#include "igesimporter.h"
#include <iostream>

IGESImporter::IGESImporter(const QString &filename) : reader()
{
    stat = reader.ReadFile (filename.toStdString ().c_str ());
}

IGESImporter::~IGESImporter()
{

}


bool IGESImporter::import () {
    iterateWires();
    return true;
}

void IGESImporter::iterateWires() {
    std::stringstream output;
    if (stat == IFSelect_RetDone) {
        Handle(TColStd_HSequenceOfTransient) list = reader.GiveList();
        reader.TransferList(list);

        TopoDS_Shape shape = reader.OneShape();
        TopExp_Explorer explorer;

        int i = 0;
        for (explorer.Init (shape, TopAbs_EDGE);
             explorer.More();
             explorer.Next ()) {
            Standard_Boolean isDegenerated = BRep_Tool::Degenerated ((const TopoDS_Edge&)explorer.Current ());
            Standard_Boolean isGeometric = BRep_Tool::IsGeometric ((const TopoDS_Edge&) explorer.Current ());
            Standard_Boolean isClosed = BRep_Tool::IsClosed (explorer.Current ());

            double start = 0.0, end = 1.0;
            Handle(Geom_Curve) curve = BRep_Tool::Curve (
                        (const TopoDS_Edge&) explorer.Current (), start, end);
            if (!curve.IsNull ()) {
                for (double d = start; d < end; d += (end - start)*0.1) {
                    gp_Pnt point = curve->Value (d);
                    double x = point.X();
                    double y = point.Y();
                    double z = point.Z();
                    output << "x="<< x << " y=" << y << " z="<< z << '\n';
                }
            }
            i++;
        }
        this->output = QString(output.str ().c_str ());
    }
}
