#ifndef GUIWindow_H
#define GUIWindow_H

#include <vtkSmartPointer.h>

#include <QMainWindow>
#include <QtWidgets>
#include <opencv2/opencv.hpp>

// Forward Qt class declarations
class Ui_GUIWindow;

class GUIWindow : public QMainWindow
{
	Q_OBJECT
public:

	// Constructor/Destructor
	GUIWindow(); 
	~GUIWindow() {};

	public slots:
		void Btn_Load_Extrinsic_Click();
		void Btn_Load_Intrinsic_Click();
		void Btn_Next_Frame_Click();

private:

	// Designer form
	Ui_GUIWindow *ui;
};

#endif