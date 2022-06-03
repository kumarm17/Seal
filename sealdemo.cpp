#include<iostream>
#include <fstream> 
#include <string>
//BABA was here !!!
#include"seal/seal.h"
#include"sealtool.h"
#include"myfunction.h"

using namespace std;
using namespace seal;
// using namespace ntl;

size_t row_size =3;

int main()
{            

	print_example_banner("Example: CKKS Basics");
	cout<<endl;
    EncryptionParameters parms(scheme_type::ckks);
    size_t poly_modulus_degree = 8192;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::Create(poly_modulus_degree, { 60, 40, 40, 60 }));
    
    double scale = pow(2.0, 40);

    SEALContext context(parms);
    print_parameters(context);

    KeyGenerator keygen(context);
    auto secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);
    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);
    GaloisKeys gal_keys;
    keygen.create_galois_keys(gal_keys);
    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context);
    Decryptor decryptor(context, secret_key);

    CKKSEncoder encoder(context);
    size_t slot_count = encoder.slot_count();
    cout << "Number of slots: " << slot_count << endl;
    
    vector<vector<double>> input_vector(row_size);
    


    input_vector = gen_mat(row_size, slot_count);
    vector<vector<Plaintext>> plainvec(2);
    vector<Plaintext> plain_input(row_size);
    vector<Ciphertext> cipher_input(row_size);
    for (int i = 0; i < row_size; ++i)
    {
        encoder.encode(input_vector[i], scale, plain_input[i]);
        encryptor.encrypt(plain_input[i], cipher_input[i]);
    }

    Ciphertext cipher_input_result ;
    cipher_input_result = multiply_and_refresh(evaluator, cipher_input[0], cipher_input[1], cipher_input_result, relin_keys);
    match_parms_id(evaluator, cipher_input[0], cipher_input_result);
    evaluator.add(cipher_input[0], cipher_input_result, cipher_input_result);
    evaluator.rotate_vector(cipher_input_result, 4, gal_keys, cipher_input_result);
   
    // Decrypt, decode, and print the result.
   
    Plaintext plain_result;
    // decryptor.decrypt(cipher_input[1], plain_result);
    decryptor.decrypt(cipher_input_result, plain_result);
    vector<double> result;
    encoder.decode(plain_result, result);
    cout << "    + Computed result ...... Correct." << endl;
    print_vector(result,4,2);

	return 0;
}
