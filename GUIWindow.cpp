#include "GUIWindow.h"

// This is included here because it is forward declared in
// RenderWindowUISingleInheritance.h
#include "ui_GUIWindow.h"

#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>

// Constructor
GUIWindow::GUIWindow() 
{
	this->ui = new Ui_GUIWindow;
	this->ui->setupUi(this);

	// Sphere
	vtkSmartPointer<vtkSphereSource> sphereSource = 
		vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->Update();
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
	vtkSmartPointer<vtkActor> sphereActor = 
		vtkSmartPointer<vtkActor>::New();
	sphereActor->SetMapper(sphereMapper);

	// VTK Renderer
	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(sphereActor);

	// VTK/Qt wedded
	this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

	// Set up action signals and slots

	connect(this->ui->Btn_Load_Extrinsic, SIGNAL(clicked()), this, SLOT(Btn_Load_Extrinsic_Click()));
	connect(this->ui->Btn_Load_Intrinsic, SIGNAL(clicked()), this, SLOT(Btn_Load_Intrinsic_Click()));
	connect(this->ui->Btn_Next_Frame, SIGNAL(clicked()), this, SLOT(Btn_Next_Frame_Click()));
	connect(this->ui->actionOpen_Image, SIGNAL(triggered()), this, SLOT(Action_Open_Trigger()));
}
// 
// void GUIWindow::slotExit() 
// {
// 	qApp->exit();
// }

void GUIWindow::Action_Open_Trigger()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video/Image"),
		QString(), tr("Video Files (*.avi *.mp4);;Image Files (*.jpg *.png *bmp)"));
	if (!fileName.isEmpty())
	{
		this->ui->lineEdit_Vid->setText(fileName);
	}
}

void GUIWindow::Btn_Load_Extrinsic_Click()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Extrinsic File"),
		QString(), tr("XML/YML Files (*.xml *.yml);;Text Files (*.txt)"));

	cv::Mat R, T;
	if (!fileName.isEmpty())
	{
		this->ui->lineEdit_Extrinsic->setText(fileName);

		// Read camera parameters
		cv::FileStorage fs;
		if (!fs.open(fileName.toStdString(), cv::FileStorage::READ))
		{
			QMessageBox::information(this, "Error", "Cannot open the file");
		}
		fs["R"] >> R; fs["T"] >> T;
		fs.release();
		QString s;
		QTextStream in(&s);
		in.setRealNumberPrecision(4);

		for(int i=0; i<R.size().height; i++)
		{
			in << "[";
			for(int j=0; j<R.size().width; j++)
			{
				in << R.at<double>(i,j);
				if(j != R.size().width-1)
					in << ", ";
				else
					in << ", " << T.at<double>(i) << "]" << endl;
			}
		}
		ui->Label_ExMat->setText(s);
	}
}

void GUIWindow::Btn_Load_Intrinsic_Click()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Intrinsic File"),
		QString(), tr("XML/YML Files (*.xml *.yml);;Text Files (*.txt)"));

	cv::Mat M1, M2, D1, D2;
	if (!fileName.isEmpty())
	{
		this->ui->lineEdit_Intrinsic->setText(fileName);

		// Read camera parameters
		cv::FileStorage fs;
		if (!fs.open(fileName.toStdString(), cv::FileStorage::READ))
		{
			QMessageBox::information(this, "Error", "Cannot open the file");
		}
		fs["M1"] >> M1; fs["M2"] >> M2;
		fs["D1"] >> D1; fs["D2"] >> D2;
		fs.release();
		QString ls, rs;
		QTextStream lin(&ls), rin(&rs);
		lin.setRealNumberPrecision(5);
		rin.setRealNumberPrecision(5);
		for(int i=0; i<M1.size().height; i++)
		{
			lin << "[";
			rin << "[";
			for(int j=0; j<M1.size().width; j++)
			{
				lin << M1.at<double>(i,j);
				rin << M2.at<double>(i,j);
				if(j != M1.size().width-1)
				{
					lin << ", ";
					rin << ", ";
				}
				else
				{
					lin << "]" << endl;
					rin << "]" << endl; 
				}
			}
		}
		// Distortion
		lin << "[" << D1.at<double>(0) << ", " << D1.at<double>(1) << ", " << D1.at<double>(1) << ", " << D1.at<double>(3) << ", " << D1.at<double>(4) << "]" << endl;
		rin << "[" << D2.at<double>(0) << ", " << D2.at<double>(1) << ", " << D2.at<double>(1) << ", " << D2.at<double>(3) << ", " << D2.at<double>(4) << "]" << endl; 

		ui->Label_InMat_Left->setText(ls);
		ui->Label_InMat_Right->setText(rs);
	}
}

void GUIWindow::Btn_Next_Frame_Click()
{

}