// Convert file into C/C++ source code byte array
//   for embedding binary data directly into
//   source code.
//
// by Hydranix
//   This source code is hereby released into the
//    Public Domain
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdint>

#include <sys/stat.h>

int Usage(char * self = 0);

int main(int argc, char** argv)
{
  if(argc != 3)
  {
    return Usage(argv[0]);
  }

  std::ifstream infile(argv[1], std::ifstream::binary);
  std::ofstream outfile(argv[2]);
  struct stat stats = {0};
  stat(argv[1], &stats);

  int filesize = stats.st_size;
  outfile << "char filedata[] = {";
  
  std::vector<uint8_t> buffer(filesize);
  if(infile.good() && outfile.good())
  {
    infile.read(reinterpret_cast<char*>(&buffer[0]), buffer.size());
    for(int i=0;i<filesize;++i)
    {
      outfile << "0x" << std::hex << std::setw(2) << std::setfill('0') <<
      +buffer[i];
      if(i == filesize-1)
      {
        outfile << "};";
        break;
      }
      if(i % 16)
      {
        outfile << ", ";
      }
      else
      {
        outfile << ",\n                   ";
      }
    }
  }
  infile.close();
  outfile.close();
  return 0;
}

int Usage(char * self)
{
  std::cout << self << " usage:\n\n" <<
  self << " <input file> <output file>" << std::endl;
  return 1;
}