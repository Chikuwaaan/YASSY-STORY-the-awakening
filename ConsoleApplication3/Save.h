#pragma once

class Input;
class Sounds;

class Save
{
private:
    void LoadCurrent();
    void LoadProg();
    void WriteCurrent();
    void WriteProg();
public:
    static Input* inputP;
    static Sounds* soundsP;

    Save();
    void LoadOptions();
    void WriteOptions();

    void LoadProgress();
    void WriteProgress();
};

