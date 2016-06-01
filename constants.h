#ifndef CONSTANTS_H
#define CONSTANTS_H


struct meta_string
{
	uint8_t const * buffer; 
	size_t  length; 
}

struct AuthInfo
{
	struct meta_string *uid; 
	struct meta_string *pwd; 
	struct meta_string *domain; 
}; 


#ifdef __cplusplus 
	extern "C" {
#endif 
	
/* define your personal info here or use struct */
#define UID ""
#define PWD ""
#define domain ""

#ifdef __cplusplus 
}
#endif

#endif /* constants.h */

