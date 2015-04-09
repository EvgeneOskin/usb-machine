#ifndef IGESIMPORTER_H
#define IGESIMPORTER_H

#include <QString>
#include <IGESControl_Reader.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Edge.hxx>
#include <Geom_Curve.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <gp_Pnt.hxx>
#include <BRep_Tool.hxx>

class IGESImporter
{
public:
    IGESImporter(const QString &fileName);
    ~IGESImporter();
    bool import();

private:
    void iterateWires();
    IGESControl_Reader reader;
    IFSelect_ReturnStatus stat;
};

#endif // IGESIMPORTER_H
