
class scrPt{
public:
	GLint x, y;
	
};
class range{
public:
	scrPt pt1;
	scrPt pt2;
	scrPt pt3;
	scrPt pt4;
};

void setCicrle(double Xc, double Yc,float length);
void setHexagon(double Xc, double Yc,float length);
void setSquare(double Xc, double Yc,float length);

void setScale(double Xc, double Yc);
void setTrans(double Xc, double Yc);
void setRotate(double Xc, double Yc);
void highlight(range currrent, bool first);
void drawTable();
void switchs(int x, int y, scrPt pick);
