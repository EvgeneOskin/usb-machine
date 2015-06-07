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
        TopExp_Explorer wireExplorer;
        TopExp_Explorer edgeExplorer;
        wireExplorer.Init (shape, TopAbs_WIRE);
//        wireExplorer.Next ();

        int i = 0;
        for (edgeExplorer.Init (wireExplorer.Current(), TopAbs_EDGE);
             edgeExplorer.More();
             edgeExplorer.Next ()) {
            double start = 0.0, end = 1.0;
//            double previousX = 0, previousY = 0;
            Handle(Geom_Curve) curve = BRep_Tool::Curve (
                        (const TopoDS_Edge&) edgeExplorer.Current (), start, end);
            if (!curve.IsNull ()) {
                for (double d = start; d < end; d += (end - start)*0.1) {
                    gp_Pnt point = curve->Value (d);
                    double x = point.X();
                    double y = point.Y();
                    double z = point.Z();
//                    if (d == start) {
//                        previousX = x;
//                        previousY = y;
//                    } else {
//                        if (previousX == x || previousY == y) {
//                            break;
//                        }
//                    }
                    output << "x="<< x << " y=" << y << " z="<< z << '\n';
                }
            }
            i++;
        }
        this->output = QString(output.str ().c_str ());
    }
}
