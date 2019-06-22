#ifndef _FILEOP_H_
#define _FILEOP_H_
#include <fstream>
#include <string>
#include <cstdint>
namespace computational_graph
{
    typedef long long hash_t;
    typedef std::uint16_t flag_t;
    class ByteStreamHash
    {
    private:
        static const hash_t base,mod;
        hash_t curhash;
    public:
        ByteStreamHash();
        ByteStreamHash& operator<<(char ch);
        hash_t hash();
    };
    class FileReader
    {
    private:
        std::ifstream in;
    public:
        FileReader(std::string input_name);
        FileReader(const FileReader &y) =delete;
        FileReader(FileReader &&y);
        FileReader& operator=(const FileReader &y) =delete;
        template<class T>
        T read();
        template<class T>
        void read(T &x);
    };
    class FileWriter
    {
    private:
        std::ofstream out;
        ByteStreamHash hash;
    public:
        FileWriter(std::string output_name);
        FileWriter(const FileWriter &y) =delete;
        FileWriter(FileWriter &&y);
        FileWriter& operator=(const FileWriter &y) =delete;
        template<class T>
        void write(T x);
        ~FileWriter();
    };
}
#endif
