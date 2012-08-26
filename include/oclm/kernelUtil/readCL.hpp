#include <string>

std::string readCLFile(std::string clFile)
{
   using namespace std;
   FILE * pFile;
   char buffer [1000];

   string fileName = __FILE__;
   std::string replaceName = "readCL.hpp";
   fileName.replace(fileName.size() - replaceName.size(), replaceName.size(), clFile);

   pFile = fopen ( fileName.c_str(), "r");
   
   string src;


   if (pFile == NULL)
   {
       fileName = "." + clFile;
       pFile = fopen ( fileName.c_str(), "r");
   }
   string errorMessage = "Error opening file at path: " + fileName;

   if (pFile == NULL)
   {
       perror (errorMessage.c_str());
        //check if we're using Windows
       #if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)
           //if so, pause because the console usually closes at the end of execution
           system("Pause");
       #endif
       exit(1);
   }
   else
   {
     while ( ! feof (pFile) )
     {
       if ( fgets (buffer , 100 , pFile) != NULL )
           src += buffer;
     }
     fclose (pFile);
   }
   return src;
}
