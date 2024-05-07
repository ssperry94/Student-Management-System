#include <user_auth.h>

//filepath variables
std::string smanEncrypt::key_path = "C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2/key.key";

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

smanEncrypt::UserRegistrator::UserRegistrator(bool is_teacher, std::string username, std::string password)
{
    this->is_teacher = is_teacher;
    this->username = username;
    this->password = password;

    std::ifstream teacher_file, student_file;
    teacher_file.open(teacher_path);
    student_file.open(student_path);

    if(!teacher_file || !student_file)
    {
        std::cerr << "Couldn't open outfiles, please check path to outfile.\n";
        exit(1);
    }

    teacher_file.close();
    student_file.close();
}

void smanEncrypt::UserRegistrator::add_account(std::vector <uint8_t> key)
{
    std::fstream outfile;
    std::vector <uint8_t> iv(CryptoPP::AES::BLOCKSIZE);
    generate_iv(iv);

    if(is_teacher)
    {
        outfile.open(teacher_path, std::ios::app);
    }
    else
    {
        //code for student path
    }

    outfile << encrypt(username, key, iv) << ',' << encrypt(password, key, iv) << ',';
    


    outfile.close();
}

void smanEncrypt::UserRegistrator::reset()
{
    //reseting teacher login..
    std::ofstream teacher, student;
    teacher.open(teacher_path);
    student.open(student_path);

    teacher << "Username,Password,Initalization Vector\n";
    student << "Username,Password,Initalization Vector\n";

    teacher.close();
    student.close();
}