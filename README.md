# Cryptoforest

Cryptoforest is an implementation of homomorphic neural random forest which is homomorphic evaluation of [Neural Random Forest](https://arxiv.org/pdf/1604.07143.pdf) (prediction using Neural Random Forest over encrypted data). For implementation, we use homomorphic encryption library [Microsoft SEAL](https://github.com/microsoft/SEAL). Cryptoforest uses [CKKS](https://eprint.iacr.org/2016/421.pdf) encryption scheme which is implemented in SEAL to support homomorphic evaluation for approximate arithmatic.

## Contents

- [Getting started](#getting-started)
    - [Installing Microsoft SEAL](#installing-microsoft-seal)
    - [Running the codes](#running-the-codes)
    - [Running the tests](#running-the-tests)
    - [Examples](#examples)
- [CKKS Scheme](#ckks-scheme)
  - [Relinearization](#relinearization)
  - [Rescaling](#rescaling)
  - [Modulus Switching](#modulus-switching)
  - [Homomorphic operations in CKKS scheme](#homomorphic-operations-in-ckks-scheme)
- [Plaintext Matrix-Ciphertext Vector Multiplication](#plaintext-matrix-ciphertext-vector-multiplication)
- [Chebyshev Polynomial Activation Function](#chebyshev-polynomial-activation-functio)
- [Contributing](#contributing)
- [License](#license)
- [Authors](#authors)
- [Acknowledgments](#acknowledgments)

## Getting started
First install the Visual Studio 2022 with C++ CMake Tools for Windows, Clang++ (>= 5.0) or GNU G++ (>= 6.0), CMake (>= 3.13) and Xcode toolchain (>= 9.3), CMake (>= 3.13) for Windows, Linux and MacOS, respectively before installing [Microsoft SEAL](https://github.com/microsoft/SEAL) library.

### Installing Microsoft SEAL
Install SEAL globally if you have root permission as follows (for details regarding installation, please refer to [SEAL](https://github.com/microsoft/SEAL)):

```PowerShell
cmake -S . -B build
cmake --build build
sudo cmake --install build
```
### Running the codes
To use the code, run as following:
```PowerShell
git clone https://mishra_pradeep@bitbucket.org/tiicrypto/tii-cryptoforest.git
cd tii-cryptoforest
cmake .
make
./cryptoforest
```
### Running the tests

Pending

### Examples

Pending

```
Give an example
```

## CKKS Scheme

See the below diagram for high-level understanding of CKKS scheme.

<img src="diagram/ckks.jpg" width=100%>

### Homomorphic operations in CKKS scheme

We make sure the ciphertexts/plaintexts are at same level and uses same encryption parameters before any ciphertext/plaintext - ciphertext/plaintext multiplication/addition operations.
  - chipertext - ciphertext multiplication
    - we do relinearization and rescaling after ciphertext - ciphertext multiplication.
  - chipertext - plaintext multiplication
    - we just do rescaling after ciphertext - plaintext multiplication since it does not exceed the dimension of resulting ciphertext.
  - chipertext - ciphertext/plaintext addition
    - we do not need relinearization and/or rescaling since dimension and scale of resulting ciphertext will be same.
  - cyclic rotation of a vector
    - rotation also does not exceed level and scale. 

## Plaintext Matrix-Ciphertext Vector multiplication
We use matrix-vector multiplication method proposed in [Halevi and Shoup](https://www.shoup.net/papers/helib.pdf). Let $W$ ba a matrix of dimension $3 \times 3$ and $\mathbf{x}$ be a vector of dimension $3 \times 1$. Then matrix-vector multiplication can be computed as $$\mathsf{W}\cdot\mathsf{x}=\sum_{i=0}^{2}\textrm{diag}^i(\mathsf{W})\cdot \textrm{rot}^i(\mathsf{x}),$$ 
  where $\textrm{diag}^i(\mathsf{W})$ and $\textrm{rot}^i(\mathbf{x})$ are $i^{\textrm{th}}$ diagonal of matrix $\mathsf{W}$ and $i^{\textrm{th}}$ left rotation of $\mathsf{x}$, respectively.

<img src="diagram/matvec.jpg" width=100%>


## Chebyshev Polynomial Activation

A polynomial approximation is required to substitute activation functions because we are unable to compute non-linear activation functions such as sigmoid and relu functions over encrypted data. We use chebyshev polynomial approximation of degree $15$ which is $$\sum_{i=0}^{15}c_ix^i,$$ where $c_i\in \{ 0.5000, 3.2134, 0.0000, -27.1886, 0.0000, 148.4209, 0.0000, -464.3546, 0.0000,\\ 848.3555, 0.0000, -894.7264, 0.0000, 504.3227, 0.0000, -117.5446 0.0000 \}$. It can be evaluate in the following steps:
  - Compute $x^2$, relinearize and rescale it (whenever we multiply ciphertext and ciphertext, relinearization and rescaling is must therefore we ignore writing relinearize and rescale after each ciphertext-ciphertext multiplication). 
  - Compute $x^3$ by multiplying $x^2$ and $x$ and make sure $x^2$ and $x$ uses same scale and encryption parameters  before multiplying it. 
  - Compute $x^{2i-1} = x^2\cdot x^{2i-3}$ for $ i \in \[8\] $ and again make sure $x^2$ and $x^{2i-3}$ uses same scale and encryption parameters  before multiplying it.
  - Now, we have $x^{2i-1}$ for $i\in \[8\]$ at levels $\ell - i$.
  - Next, we prepare $c_{2i-1}$ by encoding in plaintext space and modulus switching at level $\ell - i$.
  - Compute the monomials $c_{2i-1}\cdot x_{2i-1}$, rescale and modulus switch to the lowest level $\ell-8$.
  - Add all these monomials using AddMany operation provided in SEAL to receive $\sum_{i=0}^{8}c_{2i-1}\cdot x_{2i-1}$. 
  - Finally, encode the constant term of chebyshev polynomial, modulus switch to $(\ell-8)^{\textrm{th}}$ level and add to the sum of monomials computed above.
To visualize all these steps, check the [Chebyshev polynomial evaluation diagram](<img src="diagram/chebyshev-polynomial.jpg" height="100%" width=100%>) and other diagrams such as [monomial evaluation](<img src="diagram/xv_element-wise.jpg" height="100%" width=100%>) in diagram folder. 


## Min Max Polynomial Activation

For better efficiency, we can use $3$-degree min max polynomial approximation $$0.500 + 0.197x + 0.4000x^3$$. Evaluation of min max polynomial approximation over encryted data can be followed from the evaluation of chebyshev polynomial activation mentioned in the above section.   

## Cryptoforest in client-server model 

<img  src="diagram/client-server-model.jpg" height="100%" width=100%>

## Contributing


---


## Authors

---


## License

---

## Acknowledgments

---
