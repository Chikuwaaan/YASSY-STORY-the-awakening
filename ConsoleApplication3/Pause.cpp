#include "Pause.h"

Pause::Pause() {
    options.RegisterButtons();
}

void Pause::Update() {
    options.Show();
    options.Update();
}

void Pause::SetBackButton() {
    options.BTNback.action = back;
}