/** @file fftpack.h 
 *                    FFTPACK
 *
 * These are the same routines provided in the CLAMS libraries that
 * were originally used in our VAX/VMS production software.
 * 
 * This was obtained from http://www.netlib.org/ which is a good
 * place to look for tested mathematical source code.
 *
 * <pre>
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 *                   version 4  april 1985
 * 
 *      a package of fortran subprograms for the fast fourier
 *       transform of periodic and other symmetric sequences
 * 
 *                          by
 * 
 *                   paul n swarztrauber
 * 
 *   national center for atmospheric research  boulder,colorado 80307
 * 
 *    which is sponsored by the national science foundation
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * </pre>
 * 
 * this package consists of programs which perform fast fourier
 * transforms for both complex and real periodic sequences and
 * certain other symmetric sequences that are listed below.
 * 
 * 1.   rffti_     initialize rfftf and rfftb
 * 2.   rfftf_     forward transform of a real periodic sequence
 * 3.   rfftb_     backward transform of a real coefficient array
 * 
 * 4.   ezffti_    initialize ezfftf and ezfftb
 * 5.   ezfftf_    a simplified real periodic forward transform
 * 6.   ezfftb_    a simplified real periodic backward transform
 * 
 * 7.   sinti_     initialize sint
 * 8.   sint_      sine transform of a real odd sequence
 * 
 * 9.   costi_     initialize cost
 * 10.  cost_      cosine transform of a real even sequence
 * 
 * 11.  sinqi_     initialize sinqf and sinqb
 * 12.  sinqf-     forward sine transform with odd wave numbers
 * 13.  sinqb_     unnormalized inverse of sinqf
 * 
 * 14.  cosqi_     initialize cosqf and cosqb
 * 15.  cosqf_     forward cosine transform with odd wave numbers
 * 16.  cosqb_     unnormalized inverse of cosqf
 * 
 * 17.  cffti_     initialize cfftf and cfftb
 * 18.  cfftf_     forward transform of a complex periodic sequence
 * 19.  cfftb_     unnormalized inverse of cfftf
 * 
 *
 * C-Header by C. Piker of the U of I, feel free to improve it.
 */

#ifndef _fftpack_H_
#define _fftpack_H_

/** initialize rfftf and rfftb
 * 
 * subroutine rffti initializes the array wsave which is used in
 * both rfftf and rfftb. the prime factorization of n together with
 * a tabulation of the trigonometric functions are computed and
 * stored in wsave.
 * 
 * input parameter
 * 
 * @param n       the length of the sequence to be transformed.
 * 
 * output parameter
 * 
 * @param wsave   a work array which must be dimensioned at least 2*n+15.
 *         the same work array can be used for both rfftf and rfftb
 *         as long as n remains unchanged. different wsave arrays
 *         are required for different values of n. the contents of
 *         wsave must not be changed between calls of rfftf or rfftb.
 */
void rffti_(const int* n, float* wsave);

/** forward transform of a real periodic sequence
 * 
 * subroutine rfftf computes the fourier coefficients of a real
 * perodic sequence (fourier analysis). the transform is defined
 * below at output parameter r.
 *
 * @Note  This transform is unnormalized since a call of rfftf
 *        followed by a call of rfftb will multiply the input
 *        sequence by n.
 * 
 * Input Parameters:
 * 
 * @param n  the length of the array r to be transformed.  the method
 *         is most efficient when n is a product of small primes.
 *         n may change so long as different work arrays are provided
 * 
 * @param r a real array of length n which contains the sequence
 *          to be transformed, the output values will overwrite the
 *          input sequence.
 * 
 * @param wsave  a work array which must be dimensioned at least 2*n+15.
 *         in the program that calls rfftf. the wsave array must be
 *         initialized by calling subroutine rffti(n,wsave) and a
 *         different wsave array must be used for each different
 *         value of n. this initialization does not have to be
 *         repeated so long as n remains unchanged thus subsequent
 *         transforms can be obtained faster than the first.
 *         the same wsave array can be used by rfftf and rfftb.
 *
 *         wsave contains results which must not be destroyed between
 *         calls of rfftf or rfftb.
 * 
 * Output Parameters:
 *
 * <code>
 * r       r(1) = the sum from i=1 to i=n of r(i)
 * 
 *         if n is even set l =n/2   , if n is odd set l = (n+1)/2
 * 
 *           then for k = 2,...,l
 * 
 *              r(2*k-2) = the sum from i = 1 to i = n of
 * 
 *                   r(i)*cos((k-1)*(i-1)*2*pi/n)
 * 
 *              r(2*k-1) = the sum from i = 1 to i = n of
 * 
 *                  -r(i)*sin((k-1)*(i-1)*2*pi/n)
 * 
 *         if n is even
 * 
 *              r(n) = the sum from i = 1 to i = n of
 * 
 *                   (-1)**(i-1)*r(i)
 * </code>
 */
void rfftf_(const int* n, float* r, const float* wsave);


/** Backward transform of a real coefficient array.
 * 
 * subroutine rfftb computes the real perodic sequence from its
 * fourier coefficients (fourier synthesis). the transform is defined
 * below at output parameter r.
 * 
 * Input Parameters:
 * 
 * @param n  the length of the array r to be transformed.  the method
 *           is most efficient when n is a product of small primes.
 *           n may change so long as different work arrays are provided
 * 
 * @param r a real array of length n which contains the sequence
 *          to be transformed, the output values will overwrite the
 *          input sequence.
 * 
 * @param wsave a work array which must be dimensioned at least 2*n+15.
 *              in the program that calls rfftb. the wsave array must be
 *              initialized by calling subroutine rffti(n,wsave) and a
 *              different wsave array must be used for each different
 *              value of n. this initialization does not have to be
 *              repeated so long as n remains unchanged thus subsequent
 *              transforms can be obtained faster than the first.
 *              the same wsave array can be used by rfftf and rfftb.
 * 
 * Output Parameters:
 *
 * <code>
 * r       for n even and for i = 1,...,n
 * 
 *              r(i) = r(1)+(-1)**(i-1)*r(n)
 * 
 *                   plus the sum from k=2 to k=n/2 of
 * 
 *                    2.*r(2*k-2)*cos((k-1)*(i-1)*2*pi/n)
 * 
 *                   -2.*r(2*k-1)*sin((k-1)*(i-1)*2*pi/n)
 * 
 *         for n odd and for i = 1,...,n
 * 
 *              r(i) = r(1) plus the sum from k=2 to k=(n+1)/2 of
 * 
 *                   2.*r(2*k-2)*cos((k-1)*(i-1)*2*pi/n)
 * 
 *                  -2.*r(2*k-1)*sin((k-1)*(i-1)*2*pi/n)
 * </code>
 * @note  this transform is unnormalized since a call of rfftf
 *        followed by a call of rfftb will multiply the input
 *        sequence by n.
 * 
 * @warning wsave contains results which must not be destroyed between
 *         calls of rfftb or rfftf.
 */
void rfftb_(const int* n, float* r, const float* wsave);

/* Initialize ezfftf and ezfftb
 * 
 * subroutine ezffti initializes the array wsave which is used in
 * both ezfftf and ezfftb. the prime factorization of n together with
 * a tabulation of the trigonometric functions are computed and
 * stored in wsave.
 * 
 * input parameter
 * 
 * @param n  the length of the sequence to be transformed.
 * 
 * output parameter
 * 
 * @param wsave   a work array which must be dimensioned at least 3*n+15.
 *         the same work array can be used for both ezfftf and ezfftb
 *         as long as n remains unchanged. different wsave arrays
 *         are required for different values of n.
 */
void ezffti_(const int* n, float* wsave);


/** A simplified real periodic forward transform.
 * 
 * subroutine ezfftf computes the fourier coefficients of a real
 * perodic sequence (fourier analysis). the transform is defined
 * below at output parameters azero,a and b. ezfftf is a simplified
 * but slower version of rfftf.
 * 
 * Input Parameters:
 * 
 * @param n  the length of the array r to be transformed.  the method
 *         is must efficient when n is the product of small primes.
 * 
 * @param r a real array of length n which contains the sequence
 *          to be transformed. r is not destroyed.
 * 
 * @param wsave a work array which must be dimensioned at least 3*n+15.
 *         in the program that calls ezfftf. the wsave array must be
 *         initialized by calling subroutine ezffti(n,wsave) and a
 *         different wsave array must be used for each different
 *         value of n. this initialization does not have to be
 *         repeated so long as n remains unchanged thus subsequent
 *         transforms can be obtained faster than the first.
 *         the same wsave array can be used by ezfftf and ezfftb.
 * 
 * Output Parameters:
 * 
 * @param azero the sum from i=1 to i=n of r(i)/n
 * 
 * @param a defined below
 *
 * @param b defined below
 *
 * a,b     for n even b(n/2)=0. and a(n/2) is the sum from i=1 to
 *         i=n of (-1)**(i-1)*r(i)/n
 * 
 *         for n even define kmax=n/2-1
 *         for n odd  define kmax=(n-1)/2
 * 
 *         then for  k=1,...,kmax
 * 
 *              a(k) equals the sum from i=1 to i=n of
 * 
 *                   2./n*r(i)*cos(k*(i-1)*2*pi/n)
 * 
 *              b(k) equals the sum from i=1 to i=n of
 * 
 *                   2./n*r(i)*sin(k*(i-1)*2*pi/n)
 */
void ezfftf_(
	const int* n, const float* r, float* azero, float* a, float* b,
	const float* wsave
);

/** A simplified real periodic backward transform
 * 
 * subroutine ezfftb computes a real perodic sequence from its
 * fourier coefficients (fourier synthesis). the transform is
 * defined below at output parameter r. ezfftb is a simplified
 * but slower version of rfftb.
 * 
 * Input Parameters:
 * 
 * @param n  the length of the output array r.  the method is most
 *         efficient when n is the product of small primes.
 * 
 * @param azero the constant fourier coefficient
 * 
 * @param a,b arrays which contain the remaining fourier coefficients
 *         these arrays are not destroyed.
 * 
 *         the length of these arrays depends on whether n is even or
 *         odd.
 * 
 *         if n is even n/2    locations are required
 *         if n is odd (n-1)/2 locations are required
 * 
 * @param wsave   a work array which must be dimensioned at least 3*n+15.
 *         in the program that calls ezfftb. the wsave array must be
 *         initialized by calling subroutine ezffti(n,wsave) and a
 *         different wsave array must be used for each different
 *         value of n. this initialization does not have to be
 *         repeated so long as n remains unchanged thus subsequent
 *         transforms can be obtained faster than the first.
 *         the same wsave array can be used by ezfftf and ezfftb.
 * 
 * 
 * Output Parameters:
 * 
 * @param r The output coefficents
 * <pre>        
 *         if n is even define kmax=n/2
 *         if n is odd  define kmax=(n-1)/2
 * 
 *         then for i=1,...,n
 * 
 *              r(i)=azero plus the sum from k=1 to k=kmax of
 * 
 *              a(k)*cos(k*(i-1)*2*pi/n)+b(k)*sin(k*(i-1)*2*pi/n)
 * 
 * ********************* complex notation **************************
 * 
 *         for j=1,...,n
 * 
 *         r(j) equals the sum from k=-kmax to k=kmax of
 * 
 *              c(k)*exp(i*k*(j-1)*2*pi/n)
 * 
 *         where
 * 
 *              c(k) = .5*cmplx(a(k),-b(k))   for k=1,...,kmax
 * 
 *              c(-k) = conjg(c(k))
 * 
 *              c(0) = azero
 * 
 *                   and i=sqrt(-1)
 * 
 * *************** amplitude - phase notation ***********************
 * 
 *         for i=1,...,n
 * 
 *         r(i) equals azero plus the sum from k=1 to k=kmax of
 * 
 *              alpha(k)*cos(k*(i-1)*2*pi/n+beta(k))
 * 
 *         where
 * 
 *              alpha(k) = sqrt(a(k)*a(k)+b(k)*b(k))
 * 
 *              cos(beta(k))=a(k)/alpha(k)
 * 
 *              sin(beta(k))=-b(k)/alpha(k)
 *</pre>
 *
 */
void ezfftb_(
	const int* n, float* r, const float* azero, const float* a, const float* b,
	const float* wsave
);

/** initialize sint
 * 
 * subroutine sinti initializes the array wsave which is used in
 * subroutine sint. the prime factorization of n together with
 * a tabulation of the trigonometric functions are computed and
 * stored in wsave.
 * 
 * Input Parameter:
 * 
 * @param n  the length of the sequence to be transformed.  the method
 *         is most efficient when n+1 is a product of small primes.
 * 
 * Output Parameter:
 * 
 * @param wsave   a work array with at least int(2.5*n+15) locations.
 *         different wsave arrays are required for different values
 *         of n. the contents of wsave must not be changed between
 *         calls of sint_().
 * 
 */
void sinti_(const int* n, float* wsave);

/** Sine transform of a real odd sequence.
 *
 * subroutine sint computes the discrete fourier sine transform
 * of an odd sequence x(i). the transform is defined below at
 * output parameter x.
 * 
 * sint is the unnormalized inverse of itself since a call of sint
 * followed by another call of sint will multiply the input sequence
 * x by 2*(n+1).
 * 
 * the array wsave which is used by subroutine sint must be
 * initialized by calling subroutine sinti(n,wsave).
 * 
 * Input Parameters:
 * 
 * @param n  the length of the sequence to be transformed.  the method
 *         is most efficient when n+1 is the product of small primes.
 * 
 * @param x  an array which contains the sequence to be transformed
 *          This is also an ouput parameter
 * 
 * 
 * @param wsave   a work array with dimension at least int(2.5*n+15)
 *         in the program that calls sint. the wsave array must be
 *         initialized by calling subroutine sinti(n,wsave) and a
 *         different wsave array must be used for each different
 *         value of n. this initialization does not have to be
 *         repeated so long as n remains unchanged thus subsequent
 *         transforms can be obtained faster than the first.
 * 
 * Output Parameters:
 * 
 * Output overwrites input, after the call x has the values:
 * <code>
 * x       for i=1,...,n
 * 
 *              x(i)= the sum from k=1 to k=n
 * 
 *                   2*x(k)*sin(k*i*pi/(n+1))
 * 
 *              a call of sint followed by another call of
 *              sint will multiply the sequence x by 2*(n+1).
 *              hence sint is the unnormalized inverse
 *              of itself.
 * 
 * @note: wsave contains initialization calculations which must not be
 *         destroyed between calls of sint_().
 */
void sint_(const int* n, float* x, const float* wsave);

/** Initialize cost
 * 
 * subroutine costi initializes the array wsave which is used in
 * subroutine cost. the prime factorization of n together with
 * a tabulation of the trigonometric functions are computed and
 * stored in wsave.
 * 
 * input parameter
 * 
 * @param n  the length of the sequence to be transformed.  the method
 *         is most efficient when n-1 is a product of small primes.
 * 
 * output parameter
 * 
 * wsave   a work array which must be dimensioned at least 3*n+15.
 *         different wsave arrays are required for different values
 *         of n. the contents of wsave must not be changed between
 *         calls of cost.
 * 
 */
void costi_(const int* n, float* wsave);

/** Cosine transform of a real even sequence.
 * 
 * subroutine cost computes the discrete fourier cosine transform
 * of an even sequence x(i). the transform is defined below at output
 * parameter x.
 * 
 * cost is the unnormalized inverse of itself since a call of cost
 * followed by another call of cost will multiply the input sequence
 * x by 2*(n-1). the transform is defined below at output parameter x
 * 
 * the array wsave which is used by subroutine cost must be
 * initialized by calling subroutine costi(n,wsave).
 * 
 * Input Parameters:
 * 
 * @param n  the length of the sequence x. n must be greater than 1.
 *         the method is most efficient when n-1 is a product of
 *         small primes.
 * 
 * @param x an array which contains the sequence to be transformed, this
 *         is also the output parameter.
 * 
 * @param wsave a work array which must be dimensioned at least 3*n+15
 *         in the program that calls cost. the wsave array must be
 *         initialized by calling subroutine costi(n,wsave) and a
 *         different wsave array must be used for each different
 *         value of n. this initialization does not have to be
 *         repeated so long as n remains unchanged thus subsequent
 *         transforms can be obtained faster than the first.
 * 
 * Output Parameters:
 *
 * @param x Outputs defined below are stored here, overwriting the
 *          input data.
 * <pre>
 * x       for i=1,...,n
 * 
 *             x(i) = x(1)+(-1)**(i-1)*x(n)
 * 
 *              + the sum from k=2 to k=n-1
 * 
 *                  2*x(k)*cos((k-1)*(i-1)*pi/(n-1))
 * 
 *              a call of cost followed by another call of
 *              cost will multiply the sequence x by 2*(n-1)
 *              hence cost is the unnormalized inverse
 *              of itself.
 * </pre>
 *
 * @warning wsave contains initialization calculations which must not be
 *         destroyed between calls of cost_.
 */
void cost_(const int* n,float* x, const float* wsave);


/** Initialize sinqf and sinqb
 * 
 * subroutine sinqi initializes the array wsave which is used in
 * both sinqf and sinqb. the prime factorization of n together with
 * a tabulation of the trigonometric functions are computed and
 * stored in wsave.
 * 
 * Input Parameter:
 * 
 * @param n  the length of the sequence to be transformed. the method
 *         is most efficient when n is a product of small primes.
 * 
 * Output Parameter:
 * 
 * @param wsave   a work array which must be dimensioned at least 3*n+15.
 *         the same work array can be used for both sinqf and sinqb
 *         as long as n remains unchanged. different wsave arrays
 *         are required for different values of n. the contents of
 *         wsave must not be changed between calls of sinqf or sinqb.
 * 
 */
void sinqi_(const int* n, float* wsave);

/** Forward sine transform with odd wave numbers
 * 
 * subroutine sinqf computes the fast fourier transform of quarter
 * wave data. that is , sinqf computes the coefficients in a sine
 * series representation with only odd wave numbers. the transform
 * is defined below at output parameter x.
 * 
 * sinqb is the unnormalized inverse of sinqf since a call of sinqf
 * followed by a call of sinqb will multiply the input sequence x
 * by 4*n.
 * 
 * the array wsave which is used by subroutine sinqf must be
 * initialized by calling subroutine sinqi(n,wsave).
 * 
 * 
 * Input Parameters:
 * 
 * @param n  the length of the array x to be transformed.  the method
 *         is most efficient when n is a product of small primes.
 * 
 * @param x  an array which contains the sequence to be transformed, this
 *         is also the output parameter.
 * 
 * wsave   a work array which must be dimensioned at least 3*n+15.
 *         in the program that calls sinqf. the wsave array must be
 *         initialized by calling subroutine sinqi(n,wsave) and a
 *         different wsave array must be used for each different
 *         value of n. this initialization does not have to be
 *         repeated so long as n remains unchanged thus subsequent
 *         transforms can be obtained faster than the first.
 * 
 * Output Parameters:
 *
 * @param x Outputs defined below are stored here, overwriting the
 *          input data.
 * <pre>
 * x       for i=1,...,n
 * 
 *              x(i) = (-1)**(i-1)*x(n)
 * 
 *                 + the sum from k=1 to k=n-1 of
 * 
 *                 2*x(k)*sin((2*i-1)*k*pi/(2*n))
 * 
 *              a call of sinqf followed by a call of
 *              sinqb will multiply the sequence x by 4*n.
 *              therefore sinqb is the unnormalized inverse
 *              of sinqf.
 * </pre>
 *
 * @warning wsave contains initialization calculations which must not be
 *         destroyed between calls of sinqf_.
 */
void sinqf_(const int* n, float* x, const float* wsave);

/** Unnormalized inverse of sinqf
 * 
 * subroutine sinqb computes the fast fourier transform of quarter
 * wave data. that is , sinqb computes a sequence from its
 * representation in terms of a sine series with odd wave numbers.
 * the transform is defined below at output parameter x.
 * 
 * sinqf is the unnormalized inverse of sinqb since a call of sinqb
 * followed by a call of sinqf will multiply the input sequence x
 * by 4*n.
 * 
 * the array wsave which is used by subroutine sinqb must be
 * initialized by calling subroutine sinqi(n,wsave).
 * 
 * 
 * Input Parameters:
 * 
 * @param n  the length of the array x to be transformed.  the method
 *         is most efficient when n is a product of small primes.
 * 
 * @param x  an array which contains the sequence to be transformed, this
 *         is also the output parameter.
 * 
 * @param wsave  a work array which must be dimensioned at least 3*n+15.
 *         in the program that calls sinqb. the wsave array must be
 *         initialized by calling subroutine sinqi(n,wsave) and a
 *         different wsave array must be used for each different
 *         value of n. this initialization does not have to be
 *         repeated so long as n remains unchanged thus subsequent
 *         transforms can be obtained faster than the first.
 * 
 * Output Parameters:
 *
 * @param x Outputs defined below are stored here, overwriting the
 *          input data.
 * <pre>
 * x       for i=1,...,n
 * 
 *              x(i)= the sum from k=1 to k=n of
 * 
 *                4*x(k)*sin((2k-1)*i*pi/(2*n))
 * 
 *              a call of sinqb followed by a call of
 *              sinqf will multiply the sequence x by 4*n.
 *              therefore sinqf is the unnormalized inverse
 *              of sinqb.
 * </pre>
 *
 * @warning wsave contains initialization calculations which must not be
 *         destroyed between calls of sinqb_().
 */
void sinqb_(const int* n, float* x, const float* wsave);

/** Initialize cosqf and cosqb
 * 
 * subroutine cosqi initializes the array wsave which is used in
 * both cosqf and cosqb. the prime factorization of n together with
 * a tabulation of the trigonometric functions are computed and
 * stored in wsave.
 * 
 * input parameter
 * 
 * @param n  the length of the array to be transformed.  the method
 *         is most efficient when n is a product of small primes.
 * 
 * output parameter
 * 
 * wsave   a work array which must be dimensioned at least 3*n+15.
 *         the same work array can be used for both cosqf and cosqb
 *         as long as n remains unchanged. different wsave arrays
 *         are required for different values of n. the contents of
 *         wsave must not be changed between calls of cosqf_() or cosqb_().
 * 
 */
void cosqi_(const int* n, float* wsave);


/** Forward cosine transform with odd wave numbers
 * 
 * subroutine cosqf computes the fast fourier transform of quarter
 * wave data. that is , cosqf computes the coefficients in a cosine
 * series representation with only odd wave numbers. the transform
 * is defined below at output parameter x
 * 
 * cosqf is the unnormalized inverse of cosqb since a call of cosqf
 * followed by a call of cosqb will multiply the input sequence x
 * by 4*n.
 * 
 * the array wsave which is used by subroutine cosqf must be
 * initialized by calling subroutine cosqi(n,wsave).
 * 
 * 
 * Input Parameters:
 * 
 * @param n  the length of the array x to be transformed.  the method
 *         is most efficient when n is a product of small primes.
 * 
 * @param x  an array which contains the sequence to be transformed, this
 *         is also the output parameter.
 * 
 * @param wsave a work array which must be dimensioned at least 3*n+15
 *         in the program that calls cosqf. the wsave array must be
 *         initialized by calling subroutine cosqi(n,wsave) and a
 *         different wsave array must be used for each different
 *         value of n. this initialization does not have to be
 *         repeated so long as n remains unchanged thus subsequent
 *         transforms can be obtained faster than the first.
 * 
 * Output Parameters:
 * @param x Outputs defined below are stored here, overwriting the
 *          input data.
 * <pre>
 * x       for i=1,...,n
 * 
 *              x(i) = x(1) plus the sum from k=2 to k=n of
 * 
 *                 2*x(k)*cos((2*i-1)*(k-1)*pi/(2*n))
 * 
 *              a call of cosqf followed by a call of
 *              cosqb will multiply the sequence x by 4*n.
 *              therefore cosqb is the unnormalized inverse
 *              of cosqf.
 * </pre>
 *
 * @warning wsave contains initialization calculations which must not
 *         be destroyed between calls of cosqf_() or cosqb_().
 * 
 */
void cosqf_(const int* n, float* x, const float* wsave);

/** Unnormalized inverse of cosqf
 *
 * subroutine cosqb_() computes the fast fourier transform of quarter
 * wave data. that is , cosqb computes a sequence from its
 * representation in terms of a cosine series with odd wave numbers.
 * the transform is defined below at output parameter x.
 * 
 * cosqb is the unnormalized inverse of cosqf since a call of cosqb
 * followed by a call of cosqf will multiply the input sequence x
 * by 4*n.
 * 
 * the array wsave which is used by subroutine cosqb must be
 * initialized by calling subroutine cosqi(n,wsave).
 * 
 * Input Parameters:
 * 
 * @param n  the length of the array x to be transformed.  the method
 *           is most efficient when n is a product of small primes.
 * 
 * x       an array which contains the sequence to be transformed
 * 
 * wsave   a work array that must be dimensioned at least 3*n+15
 *         in the program that calls cosqb. the wsave array must be
 *         initialized by calling subroutine cosqi(n,wsave) and a
 *         different wsave array must be used for each different
 *         value of n. this initialization does not have to be
 *         repeated so long as n remains unchanged thus subsequent
 *         transforms can be obtained faster than the first.
 * 
 * Output Parameter:
 *
 * @param x Outputs defined below are stored here, overwriting the
 *          input data.
 * <pre>
 * x       for i=1,...,n
 * 
 *              x(i)= the sum from k=1 to k=n of
 * 
 *                4*x(k)*cos((2*k-1)*(i-1)*pi/(2*n))
 * 
 *              a call of cosqb_() followed by a call of
 *              cosqf will multiply the sequence x by 4*n.
 *              therefore cosqf is the unnormalized inverse
 *              of cosqb_().
 * </pre>
 *
 * @warning wsave contains initialization calculations which must not
 *         be destroyed between calls of cosqb_() or cosqf_(). 
 */
void cosqb_(const int* n, float* x, const float* wsave);

/** Initialize cfftf_ and cfftb_
 * 
 * subroutine cffti_() initializes the array wsave which is used in
 * both cfftf_() and cfftb_(). the prime factorization of n together with
 * a tabulation of the trigonometric functions are computed and
 * stored in wsave.
 * 
 * Input Parameter:
 * 
 * @param n  the length of the sequence to be transformed
 * 
 * Output Parameter:
 * 
 * @param wsave   a work array which must be dimensioned at least 4*n+15
 *         the same work array can be used for both cfftf and cfftb
 *         as long as n remains unchanged. different wsave arrays
 *         are required for different values of n. the contents of
 *         wsave must not be changed between calls of cfftf_() or cfftb_().
 * 
 */
void cffti_(const int* n, float* wsave);

/** Forward transform of a complex periodic sequence
 * subroutine cfftf computes the forward complex discrete fourier
 * transform (the fourier analysis). equivalently , cfftf computes
 * the fourier coefficients of a complex periodic sequence.
 * the transform is defined below at output parameter c.
 * 
 * the transform is not normalized. to obtain a normalized transform
 * the output must be divided by n. otherwise a call of cfftf
 * followed by a call of cfftb will multiply the sequence by n.
 * 
 * the array wsave which is used by subroutine cfftf must be
 * initialized by calling subroutine cffti(n,wsave).
 * 
 * Input parameters
 * 
 * @param n  the length of the complex sequence c. the method is
 *        more efficient when n is the product of small primes. n
 * 
 * @param c  a complex array of length n which contains the sequence, 
 *         this is also the output parameter.
 * 
 * @param wsave a real work array which must be dimensioned at least 4n+15
 *         in the program that calls cfftf. the wsave array must be
 *         initialized by calling subroutine cffti(n,wsave) and a
 *         different wsave array must be used for each different
 *         value of n. this initialization does not have to be
 *         repeated so long as n remains unchanged thus subsequent
 *         transforms can be obtained faster than the first.
 *         the same wsave array can be used by cfftf and cfftb.
 * 
 * Output Parameter:
 * 
 * @param c Function output which overwrites the input values, the 
 *         content of which is defined below.
 * <pre>
 * c      for j=1,...,n
 * 
 *            c(j)=the sum from k=1,...,n of
 * 
 *                  c(k)*exp(-i*(j-1)*(k-1)*2*pi/n)
 * 
 *                        where i=sqrt(-1)
 * </pre>
 *
 * @waning wsave contains initialization calculations which must not be
 *         destroyed between calls of subroutine cfftf_() or cfftb_()
 * 
 */
void cfftf_(const int* n, float* c, const float* wsave);

/** Unnormalized inverse of cfftf_
 * 
 * subroutine cfftb computes the backward complex discrete fourier
 * transform (the fourier synthesis). equivalently , cfftb computes
 * a complex periodic sequence from its fourier coefficients.
 * the transform is defined below at output parameter c.
 * 
 * a call of cfftf_() followed by a call of cfftb_() will multiply the
 * sequence by n.
 * 
 * the array wsave which is used by subroutine cfftb must be
 * initialized by calling subroutine cffti(n,wsave).
 * 
 * Input Parameters:
 * 
 * @param n  the length of the complex sequence c. the method is
 *           more efficient when n is the product of small primes.
 * 
 * @param c a complex array of length n which contains the sequence
 * 
 * @param wsave  a real work array which must be dimensioned at least 4n+15
 *         in the program that calls cfftb_(). The wsave array must be
 *         initialized by calling subroutine cffti(n,wsave) and a
 *         different wsave array must be used for each different
 *         value of n. this initialization does not have to be
 *         repeated so long as n remains unchanged thus subsequent
 *         transforms can be obtained faster than the first.
 *         the same wsave array can be used by cfftf_() and cfftb_().
 * 
 * Output Parameters:
 *
 * @param c Function output overwrites the input the values in C are.
 *
 * <code>
 * c      for j=1,...,n
 * 
 *            c(j)=the sum from k=1,...,n of
 * 
 *                  c(k)*exp(i*(j-1)*(k-1)*2*pi/n)
 * 
 *                        where i=sqrt(-1)
 * </code>
 *
 * @waning wsave contains initialization calculations which must not be
 *         destroyed between calls of subroutine cfftf_() or cfftb_()
 * 
 */
void cfftb_(const int* n, float* c, const float* wsave);


#endif
