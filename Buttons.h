#pragma once

#ifndef BUTTON_HEADER
#define BUTTON_HEADER

#include "Graphics.h"
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>

enum BUTTON_TYPE { GENERIC, SLIDER };

// Button class that allows the user to click.
class GenericButton {
public:
	const wchar_t* text;
	BUTTON_TYPE type = GENERIC;
	bool isTabButton = false;

	bool pressed = false;

	GenericButton(const wchar_t* text) {
		this->text = text;
	}

	GenericButton(const wchar_t* text, bool isTabButton) {
		this->text = text;
		this->isTabButton = isTabButton;
	}

	virtual void Draw(Graphics* graphics, int i, int x, int y, bool selected) {
		if (selected) graphics->DrawFilledRectangle(0, 25 + (i * 25), 300, 25, 0.0f, 0.41f, 0.41f, 0.3f);
		if (this->isTabButton) graphics->DrawString(L"▶", 280, 25 + (i * 25), 0.0f, 1.0F, 1.0F, 1.0f);;
		graphics->DrawString(text, 5, 25 + (i * 25), 0.0f, 1.0F, 1.0F, 1.0f);
	}

	virtual void Press() {
		pressed = true;
	}

	virtual bool wasPressed() {
		if (pressed) {
			pressed = false;
			return true;
		}
		return false;
	}

	BUTTON_TYPE getType() {
		return this->type;
	}
};

class ToggleButton : public GenericButton {
public:
	// Toogle Booleans
	bool toggled = false;
	bool enabled = false;
	bool disabled = false;

	ToggleButton(const wchar_t* text) : GenericButton(text) {
		this->text = text;
	}

	virtual void Draw(Graphics* graphics, int i, int x, int y, bool selected) override {
		if (selected) graphics->DrawFilledRectangle(0, 25 + (i * 25), 300, 25, 0.0f, 0.41f, 0.41f, 0.3f);
		if (this->toggled) {
			graphics->DrawOutlinedRectangle(280, 25 + (i * 25) + 5, 15, 15, 1.0f, 1.0f, 1.0f, 1.0f);
		}
		else {
			graphics->DrawRectangle(280, 25 + (i * 25) + 5, 15, 15, 0.5f, 0.5f, 0.5f, 1.0f);
		}

		graphics->DrawString(text, 5, 25 + (i * 25), 0.0f, 1.0F, 1.0F, 1.0f);
	}

	virtual void Press() override {
		this->toggled = !this->toggled;
		if (!this->toggled) {
			disabled = true;
		}
		else {
			enabled = true;
		}
	}

	virtual bool isToggled() {
		return this->toggled;
	}

	virtual bool wasDisabled() {
		if (disabled) {
			disabled = false;
			return true;
		}
		return false;
	}

	virtual bool wasEnabled() {
		if (enabled) {
			enabled = false;
			return true;
		}
		return false;
	}
};

class SliderButton : public GenericButton {
public:
	float min;
	float max;
	float increment;
	float current;
	bool useMultiplier = false;

	SliderButton(const wchar_t* text, float min, float max, float increment) : GenericButton(text) {
		this->min = min;
		this->max = max;
		this->increment = increment;
		this->current = 0;
		this->type = SLIDER;
	}

	SliderButton(const wchar_t* text, float min, float max, float increment, bool useMultiplier) : GenericButton(text) {
		this->min = min;
		this->max = max;
		this->increment = increment;
		this->current = 0;
		this->type = SLIDER;
		this->useMultiplier = useMultiplier;
	}

	virtual void Draw(Graphics* graphics, int i, int x, int y, bool selected) override {
		if (selected) graphics->DrawFilledRectangle(0, 25 + (i * 25), 300, 25, 0.0f, 0.41f, 0.41f, 0.3f);
		std::wstringstream stream;
		stream << std::fixed << std::setprecision(2) << this->current;
		std::wstring str = stream.str();
		int length = str.length();

		graphics->DrawString(str.c_str(), 300 - (length*10) - 10, 25 + (i * 25), 0.0f, 1.0F, 1.0F, 1.0f);
		graphics->DrawString(L"❮", 285 - (length * 10) - 8, 25 + (i * 25), 0.0f, 1.0F, 1.0F, 1.0f);
		graphics->DrawString(L"❯", 285, 25 + (i * 25), 0.0f, 1.0F, 1.0F, 1.0f);
		graphics->DrawString(text, 5, 25 + (i * 25), 0.0f, 1.0F, 1.0F, 1.0f);
	}

	virtual void increase() {
		int multiplier = 1; 
		if(useMultiplier) multiplier = (std::abs(current)) / 10;
		if (multiplier < 1) multiplier = 1;
		this->current += increment * multiplier;
		if (this->current > max) this->current = max;
		if (this->current < min) this->current = min;
	}

	virtual void decrease() {
		int multiplier = 1;
		if (useMultiplier) multiplier = (std::abs(current)) / 10;
		if (multiplier < 1) multiplier = 1;
		this->current -= increment * multiplier;
		if (this->current > max) this->current = max;
		if (this->current < min) this->current = min;
	}

	virtual float getValue() {
		return this->current;
	}

	virtual void setValue(float value) {
		this->current = value;
	}

	virtual void update(float value) {
		setValue(value);
	}
};

#endif