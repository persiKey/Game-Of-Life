#ifndef FROM_FILE_FILLER_HPP
#define FROM_FILE_FILLER_HPP

#include "ICheckBoardFiller.hpp"
#include <string>

namespace GameOfLife
{

class FromFileFiller : public ICheckBoardFiller
{
public:
    FromFileFiller(std::string file_path);
    virtual ~FromFileFiller() = default;

    void Fill(std::shared_ptr<ICheckBoard> checkboard) override;
private:
    std::string m_file_path;
};

} // namespace GameOfLife


#endif