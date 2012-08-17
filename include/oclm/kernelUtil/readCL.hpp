#ifndef std::string
    #include <string>
#endif

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

   string errorMessage = "Error opening file at path: " + fileName;

   if (pFile == NULL)
   {
       perror (fileName.c_str());
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
