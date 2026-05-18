#pragma once

class Input;
class Sounds;

class Save
{
private:
    void LoadProg(int slot);
    void WriteCurrent(int slot);
    void WriteProg(int slot);
public:
    static Input* inputP;
    static Sounds* soundsP;

    Save();
    void LoadOptions();
    void WriteOptions();

    void LoadCurrent(int slot, bool Init);
    void LoadProgress(int slot);
    void WriteProgress(int slot);
};

