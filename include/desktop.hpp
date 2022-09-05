#include <string>

// AppRun data
std::string appRun = "#!/bin/sh\nSELF=$(readlink -f \"$0\")\nHERE=${SELF%/*}\nEXEC=$(grep -e '^Exec=.*' \"${HERE}\"/*.desktop | head -n 1 | cut -d \"=\" -f 2 | cut -d \" \" -f 1)\nexec \"${HERE}/usr/bin/${EXEC}\"\n";

// returns the .desktop file (with the passed exec as the exec)
std::string desktopFile(std::string exec){
	return "[Desktop Entry]\nName=\nExec="+exec+"\nIcon=mt\nType=Application\nCategories=Game;";
}
