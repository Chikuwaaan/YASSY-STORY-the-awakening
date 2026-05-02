#pragma once

class Input;
class Sounds;

class Save
{
private:
    void LoadCurrent(int slot);
    void LoadProg(int slot);
    void WriteCurrent(int slot);
    void WriteProg(int slot);
public:
    static Input* inputP;
    static Sounds* soundsP;

    Save();
    void LoadOptions();
    void WriteOptions();

    void LoadProgress(int slot);
    void WriteProgress(int slot);
};

