#include <string>  // for string, basic_string
#include <fstream> 
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Radiobox, Renderer, Tab, Toggle, Vertical
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for Element, separator, operator|, vbox, border
#include <iostream> 
using namespace ftxui;
int main(int argc, char* argv[]) {
	std::ifstream file(argv[1]);
	if(!file){
		std::cerr<<"Couldn't load file\n";
	}
	std::string fileContents="";
	std::string str;
	while(std::getline(file, str)){
		fileContents+=str+"\n";
	}
	std::string inputString=fileContents;
	Component input=Input(&inputString, ""); 
  auto container = Container::Vertical({
			input,
  });
	if(argc<2){
		std::cerr<<"less arguments";
		std::exit(1);
	}
		auto renderer = Renderer(container, [&] {
				return vbox({
							hbox(text((std::string)argv[1])),
							separator(),
							hbox(bgcolor(Color::Black, input->Render())),
						})|border; 
  });
  auto screen = ScreenInteractive::Fullscreen();
  screen.Loop(renderer);
	std::ofstream outFile;
	outFile.open(argv[1]);
	outFile<<inputString;
	outFile.close();
}
