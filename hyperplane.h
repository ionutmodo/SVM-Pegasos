#ifndef _HYPERPLANE_H_
#define _HYPERPLANE_H_

/// Description:
///     Represents parameters for a hyperplane of equation:
/// b + w0 x1 + w1 x1 + ... + wd-1 xd-1 = 0
struct _Hyperplane
{
    int d;     /// space dimension of data
    double b;  /// the bias (intercept)
    double *w; /// the parameters
};
typedef struct _Hyperplane Hyperplane;

/// Description:
///     Dynamic memory allocation for a Hyperplane variable
/// Parameters:
///     d - space dimension of data
/// Returns:
///     A pointer to the variable that is dynamically allocated
Hyperplane* allocHyperplane(int d);

/// Description:
///     Prints information for a hyperplane
/// Parameters:
///     H - a pointer to a Hyperplane variable
/// Returns:
///     Nothing
void printHyperplane(Hyperplane *H);

/// Description:
///     Serializes a hyperplane variable
/// Parameters:
///     H - a pointer to a Hyperplane variable
///     fileName - the name of the file to save the information to
/// Returns:
///     A pointer to the variable that is dynamically allocated
void dumpHyperplane(Hyperplane *H, char *fileName);


/// Description:
///     Deserializes a hyperplane variable saved to a file
/// Parameters:
///     fileName - the name of the file to load the information from
/// Returns:
///     A pointer to the variable that is dynamically allocated
Hyperplane* loadHyperplane(char *fileName);

/// Description:
///     Frees the memory of a variable
/// Parameters:
///     H - an addres of a pointer to a Hyperplane variable
/// Returns:
///     A pointer to the variable that is dynamically allocated
void deleteHyperplane(Hyperplane **H);

#endif // _HYPERPLANE_H_