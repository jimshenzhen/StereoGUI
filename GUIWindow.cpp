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
}
// 
// void GUIWindow::slotExit() 
// {
// 	qApp->exit();
// }

void GUIWindow::Btn_Load_Extrinsic_Click()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Extrinsic File"),
		QString(), tr("Text Files (*.txt);;XML/YML Files (*.xml *.yml)"));

	if (!fileName.isEmpty())
	{
		this->ui->lineEdit_Extrinsic->setText(fileName);
// 		QFile file(fileName);
// 		if (!file.open(QIODevice::ReadOnly))
// 		{
// 			QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
// 			return;
// 		}
// 		QTextStream in (&file);
// 		ui->textEdit->setText(in.readAll());
// 		file.close();
	}
}

void GUIWindow::Btn_Load_Intrinsic_Click()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Intrinsic File"),
		QString(), tr("Text Files (*.txt);;XML/YML Files (*.xml *.yml)"));

	if (!fileName.isEmpty())
	{
		this->ui->lineEdit_Intrinsic->setText(fileName);
		// 		QFile file(fileName);
		// 		if (!file.open(QIODevice::ReadOnly))
		// 		{
		// 			QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
		// 			return;
		// 		}
		// 		QTextStream in (&file);
		// 		ui->textEdit->setText(in.readAll());
		// 		file.close();
	}
}

void GUIWindow::Btn_Next_Frame_Click()
{
	QString ss("1 2 3\n 4 5 6\n 7 8 9");
	this->ui->test_label->setText(ss);
}