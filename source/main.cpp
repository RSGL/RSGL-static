#include <iostream>
#include <vector>
#include "../include/desktop.hpp"

bool appImage = false; // if we're creating an appImage

// libs to be linked (default : static)
std::string libs = "/usr/local/lib/libRSGL.a -lGL -lfreetype -lX11";

std::vector<std::string> bin, lib, res; // data for the app
char cur = 'b'; // bin by default 
std::string name; // name of the app 

int main(int args, char** argv){
	for (int i=1; i < args; i++){
		// if shared, just link shared RSGL
		if (std::string(argv[i]) == "-shared") 
			libs = "-lRSGL";
		// if an appimage is being made
		else if (std::string(argv[i]) == "-appImage"){
			appImage = true;
		}
		// accept as an arg for creating an appimage of we're
		else if (appImage){
			if (argv[i][0] == '-') 
				cur = argv[i][1]; // we're currently getting ..
			
			else if (name.empty()){
				switch(cur){
					case 'b': // get bins
						bin.insert(bin.end(), std::string(argv[i]));
						break;
					case 'l': // get libs
						lib.insert(lib.end(), std::string(argv[i]));
						break;
					case 'r': // get res
						res.insert(res.end(), std::string(argv[i]));
						break;
					case 'o': // get the name
						name = std::string(argv[i]);
						break;
					default: 
						break;
				}
			}
			if (!name.empty()){
				// make the appImage
				
				std::string file, dir = name+".AppDir";
				
				// make the usr folders
				std::string cmd = "mkdir " + dir + " "
								+ dir + "/usr "
								+ dir + "/usr/bin "
								+ dir + "/usr/lib";
				
				system(cmd.c_str());

				// make empty svg file for desktop
				file = dir+"/mt.svg"; // full file name
				
				FILE* f = fopen(file.c_str(), "w+");
				fclose(f);

				// make the desktop file
				file = dir+"/"+name+".desktop"; // full file name
				
				f = fopen(file.c_str(), "w+");
				
				fputs(desktopFile(name).c_str(),f); // write the desktop data into the file
				
				fclose(f);			

				// make the AppRun fil
				file = dir+"/"+"AppRun"; // full file name
				f = fopen(file.c_str(), "w+");
				
				fputs(appRun.c_str(),f); // write the desktop data into the file
				
				fclose(f);	

				// give AppRun rw perms
				cmd = "chmod +x " + file;
				system(cmd.c_str());

				// copy the bin files over
				for (auto& f : bin){
					std::string cmd = "cp -r \"";	
					cmd += f + "\" " + dir + "//usr/bin";
					
					system(cmd.c_str());
				}

				// copy the res files over
				for (auto& f : res){
					std::string cmd = "cp -r \"";	
					cmd += f + "\" " + dir;
					
					system(cmd.c_str());
				}


				// copy the lib files over
				for (auto& f : lib){
					std::string cmd = "cp -r \"";	
					cmd += f + "\" " + dir + "//usr/lib";
					
					system(cmd.c_str());
				}
			
				// generate the appImage
				cmd = "ARCH=x86_64 appimagetool " + dir + "/ " + name + ".appImage"; 
				
				system(cmd.c_str());

				// clean up
				cmd = "rm -r " + dir;

				//system(cmd.c_str());
			}
		}
	}
	
	// sends args
	std::cout << libs;
}
