#include <user_auth.h>

//filepath variables
std::string smanEncrypt::key_path = "key/key.key";
std::string smanEncrypt::teacher_path = "CSV Files/logincsvs/teacher_login.csv";
std::string smanEncrypt::student_path = "CSV Files/logincsvs/student_login.csv";

//non-class namespace functions
std::string smanEncrypt::encrypt(std::string &input, std::vector <uint8_t> key, std::vector <uint8_t> iv)
{
    std::string encrypted_text;

    auto aes = CryptoPP::AES::Encryption(key.data(), key.size());
    auto aes_cbc = CryptoPP::CBC_Mode_ExternalCipher::Encryption(aes, iv.data());

    CryptoPP::StringSource ss(
    input,
    true,
    new CryptoPP::StreamTransformationFilter(
        aes_cbc,
        new CryptoPP::Base64Encoder(
            new CryptoPP::StringSink(encrypted_text),
            false
            )
        )
    );

    return encrypted_text;
}

std::string smanEncrypt::decrypt(std::string &input, std::vector <uint8_t> key, std::vector <uint8_t> iv)
{
    std::string decrypted_text;

    auto aes = CryptoPP::AES::Decryption(key.data(), key.size());
    auto aes_cbc = CryptoPP::CBC_Mode_ExternalCipher::Decryption(aes, iv.data());

    CryptoPP::StringSource ss(
    input,
    true,
    new CryptoPP::Base64Decoder(
        new CryptoPP::StreamTransformationFilter(
            aes_cbc,
            new CryptoPP::StringSink(decrypted_text)
            )
        )
    );

    return decrypted_text;
}

void smanEncrypt::generate_key(size_t key_size)
{
    std::ofstream keyfile;
    keyfile.open(key_path);
    if(!keyfile)
    {
        std::cout << "File couldn't be opened.\n";
        return;
    }
    std::vector <uint8_t> key(key_size);
    CryptoPP::NonblockingRng rng;
    rng.GenerateBlock(key.data(), key.size());

    for(uint8_t k : key)
    {
        keyfile << k;
    }
    keyfile.close();
}

//read all data from .key file, then pump into a string, then turn string into a vector
void smanEncrypt::retrieve_key(std::vector <uint8_t> &key)
{   
    std::string key_str; 
    CryptoPP::FileSource infile(key_path.c_str(), true, new CryptoPP::StringSink(key_str)); 

    for(int i = 0; i < key.size(); i++)
    {
        key[i] = key_str[i];
    }
    key.shrink_to_fit();
}

void smanEncrypt::generate_iv(std::vector <uint8_t> &iv)
{
    CryptoPP::NonblockingRng rand;
    rand.GenerateBlock(iv.data(), iv.size());
}

//UserRegistrator class functions

smanEncrypt::UserCommon::UserCommon(bool is_teacher, std::string username, std::string password)
{
    this->is_teacher = is_teacher;
    this->username = username;
    this->password = password;

    if(is_teacher)
    {
        filepath = smanEncrypt::teacher_path;
    }
    else
    {
        filepath = smanEncrypt::student_path;
    }

    std::ifstream file{filepath};
    if(!file)
    {
        std::cerr << "Couldn't open outfile. Please check file path.\n";
        exit(1);
    }

    file.close();
}

smanEncrypt::UserRegistrator::UserRegistrator(bool is_teacher, std::string username, std::string password):
smanEncrypt::UserCommon::UserCommon(is_teacher, username, password)
{
    //see constructor for UserCommon
}

int smanEncrypt::UserRegistrator::add_account(std::vector <uint8_t> key)
{
    std::string idnum;
    std::fstream outfile{filepath, std::ios::app};
    if(!outfile)
    {
        std::cout << "Cannot open file.\n";
        return 1;
    }

    if(!is_teacher)
    {
        Teacher get_id_tech;
        std::cin.sync();
        idnum = get_id_tech.find_student();

        if(idnum == "1")
        {
            std::cout << "Student not found. Please ensure that you are registered by your teacher beforehand.\n";
            return 1;
        }
    }

    std::vector <uint8_t> iv(CryptoPP::AES::BLOCKSIZE);
    generate_iv(iv);

    outfile << encrypt(username, key, iv) << ',' << encrypt(password, key, iv) << ',';
    write_iv(outfile, iv);

    
    if(!is_teacher)
    {
        idnum = encrypt(idnum, key, iv);
        write_idnum(outfile, idnum);
    }


    outfile.close();
    return 0;
}

void smanEncrypt::UserRegistrator::write_iv(std::fstream &outfile, std::vector <uint8_t> &iv)
{
    //turn vector into base64 string
    std::string iv_base64;
    CryptoPP::StringSource(
        iv.data(),
        iv.size(),
        true,
        new CryptoPP::Base64Encoder(
            new CryptoPP::StringSink(
                iv_base64
            ),
            false
        )
    );

    //adds an endline character if user is a teacher, leaves it off if student
    if(is_teacher)
    {
        outfile << iv_base64 << ",\n";
    }
    else
    {
        outfile << iv_base64 << ",";
    }

}

void smanEncrypt::UserRegistrator::write_idnum(std::fstream &outfile, std::string &idnum)
{
    if(is_teacher)
    {
        std::cerr << "ERROR: must be a student to have an id number. Aborting program.\n";
        exit(1);
    }

    outfile << idnum << ",\n";
}

smanEncrypt::LoggingIn::LoggingIn(bool is_teacher, std::string username, std::string password):
smanEncrypt::UserCommon::UserCommon(is_teacher, username, password)
{
    //see constructor for UserCommon
}

/*Reads iv from respective CSV file and stores it in the iv vector
-Should only ever be called after username and password have been gotten, and file pointer is pointing at it*/
void smanEncrypt::LoggingIn::retrieve_iv(std::ifstream &infile, std::vector <uint8_t> &iv)
{
    std::string iv_str, iv_str_decoded;

    std::getline(infile, iv_str, ',');

    std::stringstream ss(iv_str);
    CryptoPP::FileSource(
        ss,
        true,
        new CryptoPP::Base64Decoder(
            new CryptoPP::StringSink(
                iv_str_decoded
            )
        )
    );

    for(int i = 0; i < iv_str_decoded.length(); i++)
    {
        iv[i] = iv_str_decoded[i];
    }
}

//populates username, password, and iv to compare in handle_logging_in(). takes a streampos to keep track of each line in file until the end of file is reached
void smanEncrypt::LoggingIn::retreive_account(std::string &entered_username, std::string &entered_password, std::vector <uint8_t> &iv, std::streampos &current_pos)
{
    std::ifstream infile{filepath, std::ios::binary};

    if(!infile)
    {
        std::cerr << "Cannot open file.\n";
        return;
    }
    infile.seekg(current_pos);
    //if at the beginning of file, skip headers
    if(current_pos == 0)
    {
        std::string *firstline = new std::string;
        std::getline(infile, *firstline);
        delete firstline;
    }


    std::getline(infile, entered_username, ',');
    std::getline(infile, entered_password, ',');


    retrieve_iv(infile, iv);
    current_pos = infile.tellg();
    infile.close();
}

void smanEncrypt::LoggingIn::retreive_account(std::string &entered_username, std::string &entered_password, std::vector <uint8_t> &iv, std::string &idnum, std::streampos &current_pos)
{
    std::ifstream infile{filepath, std::ios::binary};

    if(!infile)
    {
        std::cerr << "Cannot open file.\n";
        return;
    }
    infile.seekg(current_pos);
    //if at the beginning of file, skip headers
    if(current_pos == 0)
    {
        std::string *firstline = new std::string;
        std::getline(infile, *firstline);
        delete firstline;
    }


    std::getline(infile, entered_username, ',');
    std::getline(infile, entered_password, ',');


    retrieve_iv(infile, iv);

    std::getline(infile, idnum, ',');
    
    current_pos = infile.tellg();
    infile.close();
}

void smanEncrypt::UserRegistrator::reset()
{
    //reseting teacher login..
    std::ofstream file{filepath};

    if(is_teacher)
    {
        file << "Username,Password,Initalization Vector\n";
    }
    else
    {
        file << "Username,Password,Initalization Vector,ID Number\n";
    }
    
    file.close();
}