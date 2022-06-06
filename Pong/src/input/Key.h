#pragma once

namespace input {
	struct Key {
	public:
		Key() { IsPressed = false; }
		Key(bool isPressed) { IsPressed = isPressed; }
		bool IsPressed;
	};
}