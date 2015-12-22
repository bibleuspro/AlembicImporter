#include "pch.h"
#include "AlembicExporter.h"
#include "aeContext.h"
#include "aeObject.h"
#include "aeXForm.h"
#include "aePoints.h"
#include "aePolyMesh.h"
#include "aeCamera.h"


aeCLinkage aeExport aeContext* aeCreateContext(const aeConfig *conf)
{
    return new aeContext(*conf);
}

aeCLinkage aeExport void aeDestroyContext(aeContext* ctx)
{
    delete ctx;
}

aeCLinkage aeExport bool aeOpenArchive(aeContext* ctx, const char *path)
{
    return ctx->openArchive(path);
}


aeCLinkage aeExport aeObject* aeGetTopObject(aeContext* ctx)
{
    return ctx->getTopObject();
}

aeCLinkage aeExport void aeAddTime(aeContext* ctx, float time)
{
    ctx->setTime(time);
}


aeCLinkage aeExport void aeDeleteObject(aeObject *obj)
{
    delete obj;
}
aeCLinkage aeExport aeXForm* aeNewXForm(aeObject *parent, const char *name)
{
    return parent->newChild<aeXForm>(name);
}
aeCLinkage aeExport aePoints* aeNewPoints(aeObject *parent, const char *name)
{
    return parent->newChild<aePoints>(name);
}
aeCLinkage aeExport aePolyMesh* aeNewPolyMesh(aeObject *parent, const char *name)
{
    return parent->newChild<aePolyMesh>(name);
}
aeCLinkage aeExport aeCamera* aeNewCamera(aeObject *parent, const char *name)
{
    return parent->newChild<aeCamera>(name);
}

aeCLinkage aeExport void aeXFormWriteSample(aeXForm *obj, const aeXFormSampleData *data)
{
    obj->writeSample(*data);
}
aeCLinkage aeExport void aePointsWriteSample(aePoints *obj, const aePointsSampleData *data)
{
    obj->writeSample(*data);
}
aeCLinkage aeExport void aePolyMeshWriteSample(aePolyMesh *obj, const aePolyMeshSampleData *data)
{
    obj->writeSample(*data);
}
aeCLinkage aeExport void aeCameraWriteSample(aeCamera *obj, const aeCameraSampleData *data)
{
    obj->writeSample(*data);
}

aeCLinkage aeExport aeProperty* aeNewProperty(aeObject *parent, const char *name, aePropertyType type)
{
    switch (type) {
    case aePropertyType_FloatArray: return parent->newProperty<abcFloatArrayProperty>(name); break;
    case aePropertyType_IntArray:   return parent->newProperty<abcInt32ArrayProperty>(name); break;
    case aePropertyType_BoolArray:  return parent->newProperty<abcBoolArrayProperty >(name); break;
    case aePropertyType_Vec2Array:  return parent->newProperty<abcVec2ArrayProperty >(name); break;
    case aePropertyType_Vec3Array:  return parent->newProperty<abcVec3ArrayProperty >(name); break;
    case aePropertyType_Vec4Array:  return parent->newProperty<abcVec4ArrayProperty >(name); break;
    case aePropertyType_Mat44Array: return parent->newProperty<abcMat44ArrayProperty>(name); break;
    case aePropertyType_Float:  return parent->newProperty<abcFloatProperty>(name); break;
    case aePropertyType_Int:    return parent->newProperty<abcInt32Property>(name); break;
    case aePropertyType_Bool:   return parent->newProperty<abcBoolProperty >(name); break;
    case aePropertyType_Vec2:   return parent->newProperty<abcVec2Property >(name); break;
    case aePropertyType_Vec3:   return parent->newProperty<abcVec3Property >(name); break;
    case aePropertyType_Vec4:   return parent->newProperty<abcVec4Property >(name); break;
    case aePropertyType_Mat44:  return parent->newProperty<abcMat44Property>(name); break;
    }
    aeDebugLog("aeNewProperty(): unknown type");
    return nullptr;
}

aeCLinkage aeExport void aePropertyWriteArraySample(aeProperty *prop, const void *data, int num_data)
{
    if (!prop->isArray()) {
        aeDebugLog("aePropertyWriteArraySample(): property is scalar!");
        return;
    }
    prop->writeSample(data, num_data);
}

aeCLinkage aeExport void aePropertyWriteScalarSample(aeProperty *prop, const void *data)
{
    if (prop->isArray()) {
        aeDebugLog("aePropertyWriteScalarSample(): property is array!");
        return;
    }
    prop->writeSample(data, 1);
}
