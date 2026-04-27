#pragma once

class Input;
class Sounds;

class Save
{
private:

public:
    static Input* inputP;
    static Sounds* soundsP;

    Save();
    void LoadOptions();
    void WriteOptions();

    void LoadProgress();
    void WriteProgress();
};

