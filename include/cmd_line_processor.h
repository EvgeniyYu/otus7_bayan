#ifndef CMD_LINE_PROCESSOR_H_INCLUDED
#define CMD_LINE_PROCESSOR_H_INCLUDED

#include "def.h"
#include <memory>
#include <iostream>

class ICommandLineProcessor
{
public:
    virtual bool process_cmd_line(int argc, char** argv, std::ostream& ofs) = 0;
    virtual const Options& get_options() const = 0;
    virtual void print(std::ostream& ofs) const = 0;
};

class CommandLineProcessor: public ICommandLineProcessor
{
    Options options;
public:
    bool process_cmd_line(int argc, char** argv, std::ostream& ofs) override;
    const Options& get_options() const override;
    void print(std::ostream& ofs) const override;
};

using uptr_ICommandLineProcessor = std::unique_ptr<ICommandLineProcessor>;

#endif // CMD_LINE_PROCESSOR_H_INCLUDED
