#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <string>
using namespace std;
int w{Fl::w()/2}, h{Fl::h()};
struct Point{
	int x,y;
	Point(int int1,int int2) : x(int1), y(int2){}
};
struct Windows : Fl_Double_Window {
	Windows(Point topleft, int width, int height, string title)
	: Fl_Double_Window(topleft.x, topleft.y, width, height, title.c_str()){
		color(FL_BLACK);
		show();
	}
}; 
int main(){
	int w{Fl::w()/2}, h{Fl::h()};
	Windows window(Point(w,0),w,h,"Part2");
	return Fl::run();
}
