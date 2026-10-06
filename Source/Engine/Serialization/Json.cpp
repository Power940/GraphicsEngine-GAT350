#include "pch.h"
#include "Json.h"
#include <StarFallEngine.h>


namespace STR_FALL::Json
{
    bool Load(const std::string& filename, rapidjson::Document& document)
    {
        std::string buffer;
        if (!ReadTextFile(filename, buffer))
        {
            std::cerr << "Could not read file:" << filename << std::endl;
            return false;
        }

        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);
        document.ParseStream(istream);

        if (document.HasParseError())
        {
            std::cerr << "Could not parse JSON: " << filename << std::endl;
            std::cerr << "Error: " << rapidjson::GetParseError_En(document.GetParseError()) << std::endl;

            return false;
        }

        if (!document.IsObject())
        {
            std::cerr << "JSON root is not an object: " << filename << std::endl;
            return false;
        }

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, bool& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
        {
            std::cerr << "Could not read JSON value (bool): " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetBool();

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, int& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
        {
            std::cerr << "Could not read JSON value (int): " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetInt();

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
        {
            std::cerr << "Could not read JSON value (int vector): " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];
        for (int index = 0; index < value[name.c_str()].Size(); index++)
        {
            data.push_back(array[index].GetInt());
        }

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, unsigned int& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsUint())
        {
            std::cerr << "Could not read JSON value (unsigned int): " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetUint();

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, float& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber())
        {
            std::cerr << "Could not read JSON value (float): " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetFloat();

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, std::string& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
        {
            std::cerr << "Could not read JSON value (string): " << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetString();

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
        {
            std::cerr << "Could not read JSON value (string vector): " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];
        for (int index = 0; index < value[name.c_str()].Size(); index++)
        {
            data.push_back(array[index].GetString());
        }

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, std::unordered_set<std::string>& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
        {
            std::cerr << "Could not read JSON value (string vector): " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];
        for (int index = 0; index < value[name.c_str()].Size(); index++)
        {
            data.insert(array[index].GetString());
        }

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
        {
            std::cerr << "Could not read JSON value (Vector2): " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];
        if (!array[0].IsNumber()) { std::cerr << "Could not read JSON value (Vector2): " << name << std::endl; return false; }
        data.m_x = array[0].GetFloat();
        if (!array[1].IsNumber()) { std::cerr << "Could not read JSON value (Vector2): " << name << std::endl; return false; }
        data.m_y = array[1].GetFloat();

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, Vector3& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 3)
        {
            std::cerr << "Could not read JSON value (Vector3): " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];
        if (!array[0].IsNumber()) { std::cerr << "Could not read JSON value (Vector3): " << name << std::endl; return false; }
        data.m_x = array[0].GetFloat();
        if (!array[1].IsNumber()) { std::cerr << "Could not read JSON value (Vector3): " << name << std::endl; return false; }
        data.m_y = array[1].GetFloat();
        if (!array[2].IsNumber()) { std::cerr << "Could not read JSON value (Vector3): " << name << std::endl; return false; }
        data.m_z = array[2].GetFloat();

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, Vector4& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
        {
            std::cerr << "Could not read JSON value (Vector4): " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];
        if (!array[0].IsNumber()) { std::cerr << "Could not read JSON value (Vector4): " << name << std::endl; return false; }
        data.m_x = array[0].GetFloat();
        if (!array[1].IsNumber()) { std::cerr << "Could not read JSON value (Vector4): " << name << std::endl; return false; }
        data.m_y = array[1].GetFloat();
        if (!array[2].IsNumber()) { std::cerr << "Could not read JSON value (Vector4): " << name << std::endl; return false; }
        data.m_z = array[2].GetFloat();
        if (!array[3].IsNumber()) { std::cerr << "Could not read JSON value (Vector4): " << name << std::endl; return false; }
        data.m_w = array[3].GetFloat();

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, Matrix2& data)
    {
        if (value.HasMember(name.c_str()) && value[name.c_str()].IsNumber())
        {
            data = Matrix2::RotationXY(value[name.c_str()].GetFloat());
        }
        else if (value.HasMember(name.c_str()) && value[name.c_str()].IsArray() || value[name.c_str()].Size() == 4)
        {
            auto& array = value[name.c_str()];
            data = Matrix2(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat(), array[3].GetFloat());
        }

        std::cerr << "Could not read JSON value (Matrix2): " << name << std::endl;
        return false;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, Matrix3& data)
    {
        if (value.HasMember(name.c_str()) && value[name.c_str()].IsNumber())
        {
            data = Matrix3(value[name.c_str()].GetFloat());
        }
        else if (value.HasMember(name.c_str()) && value[name.c_str()].IsArray() || value[name.c_str()].Size() == 3)
        {
            auto& array = value[name.c_str()];
            data = Matrix3::RotationXYZ(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat());
        }
        else if (value.HasMember(name.c_str()) && value[name.c_str()].IsArray() || value[name.c_str()].Size() == 9)
        {
            auto& array = value[name.c_str()];
            data = Matrix3(
                array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat(),
                array[3].GetFloat(), array[4].GetFloat(), array[5].GetFloat(),
                array[6].GetFloat(), array[7].GetFloat(), array[8].GetFloat()
            );
        }

        std::cerr << "Could not read JSON value (Matrix3): " << name << std::endl;
        return false;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, Transform3D& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 9)
        {
            std::cerr << "Could not read JSON value (Transform3D): " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];
        if (!array[0].IsNumber() || !array[1].IsNumber() || !array[2].IsNumber()) { std::cerr << "Could not read JSON value (Transform3D): " << name << std::endl; return false; }
        data.m_pos = Vector3(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat());
        if (!array[3].IsNumber() || !array[4].IsNumber() || !array[5].IsNumber()) { std::cerr << "Could not read JSON value (Transform3D): " << name << std::endl; return false; }
        data.m_scale = Vector3(array[3].GetFloat(), array[4].GetFloat(), array[5].GetFloat());
        if (!array[6].IsNumber() || !array[7].IsNumber() || !array[8].IsNumber()) { std::cerr << "Could not read JSON value (Transform3D): " << name << std::endl; return false; }
        data.m_rotMat = Matrix3::RotationXYZ(array[6].GetFloat(), array[7].GetFloat(), array[8].GetFloat());

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, Camera3D& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 12)
        {
            std::cerr << "Could not read JSON value (Camera3D): " << name << std::endl;
            return false;
        }

        Transform3D t;
        float fov;
        Vector2 sd;

        auto& array = value[name.c_str()];
        if (!array[0].IsNumber() || !array[1].IsNumber() || !array[2].IsNumber()) { std::cerr << "Could not read JSON value (Camera3D): " << name << std::endl; return false; }
        t.m_pos = Vector3(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat());
        if (!array[3].IsNumber() || !array[4].IsNumber() || !array[5].IsNumber()) { std::cerr << "Could not read JSON value (Camera3D): " << name << std::endl; return false; }
        t.m_scale = Vector3(array[3].GetFloat(), array[4].GetFloat(), array[5].GetFloat());
        if (!array[6].IsNumber() || !array[7].IsNumber() || !array[8].IsNumber()) { std::cerr << "Could not read JSON value (Camera3D): " << name << std::endl; return false; }
        t.m_rotMat = Matrix3::RotationXYZ(array[6].GetFloat(), array[7].GetFloat(), array[8].GetFloat());

        if (!array[9].IsNumber()) { std::cerr << "Could not read JSON value (Camera3D): " << name << std::endl; return false; }
        fov = array[9].GetFloat();

        if (!array[10].IsNumber() || !array[11].IsNumber()) { std::cerr << "Could not read JSON value (Camera3D): " << name << std::endl; return false; }
        sd = Vector2(array[10].GetFloat(), array[11].GetFloat());

        data = Camera3D(t, fov, sd);

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, Color& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
        {
            std::cerr << "Could not read JSON value (Color): " << name << std::endl;
            return false;
        }

        auto& array = value[name.c_str()];
        if (!array[0].IsNumber()) { std::cerr << "Could not read JSON value (Color): " << name << std::endl; return false; }
        data.m_x = array[0].GetFloat();
        if (!array[1].IsNumber()) { std::cerr << "Could not read JSON value (Color): " << name << std::endl; return false; }
        data.m_y = array[1].GetFloat();
        if (!array[2].IsNumber()) { std::cerr << "Could not read JSON value (Color): " << name << std::endl; return false; }
        data.m_z = array[2].GetFloat();
        if (!array[3].IsNumber()) { std::cerr << "Could not read JSON value (Color): " << name << std::endl; return false; }
        data.m_w = array[3].GetFloat();

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, BitMaskInt& data)
    {
        if (value.HasMember(name.c_str()) && value[name.c_str()].IsNumber())
        {
            data = BitMaskInt(value[name.c_str()].GetUint());
            return true;
        }
        else if (value.HasMember(name.c_str()) && value[name.c_str()].IsArray() || value[name.c_str()].Size() == 4)
        {
            auto& array = value[name.c_str()];
            data = BitMaskInt(array[0].GetUint(), array[1].GetUint(), array[2].GetUint(), array[3].GetUint());
            return true;
        }
        else if (value.HasMember(name.c_str()) && value[name.c_str()].IsArray() || value[name.c_str()].Size() == 32)
        {
            auto& array = value[name.c_str()];
            data = BitMaskInt(
                array[0].GetUint(), array[1].GetUint(), array[2].GetUint(), array[3].GetUint(), array[4].GetUint(), array[5].GetUint(), array[6].GetUint(), array[7].GetUint(),
                array[8].GetUint(), array[9].GetUint(), array[10].GetUint(), array[11].GetUint(), array[12].GetUint(), array[13].GetUint(), array[14].GetUint(), array[15].GetUint(),
                array[16].GetUint(), array[17].GetUint(), array[18].GetUint(), array[19].GetUint(), array[20].GetUint(), array[21].GetUint(), array[22].GetUint(), array[23].GetUint(),
                array[24].GetUint(), array[25].GetUint(), array[26].GetUint(), array[27].GetUint(), array[28].GetUint(), array[29].GetUint(), array[30].GetUint(), array[31].GetUint()
            );
            return true;
        }

        std::cerr << "Could not read JSON value (BitMaskInt): " << name << std::endl;
        return false;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, Mesh3D& data)
    {
        if (!value.HasMember("points") || !value.HasMember("indices"))
        {
            return false;
        }

        const rapidjson::Value& pointsArray = value["points"];
        const rapidjson::Value& indicesArray = value["indices"];

        if (!pointsArray.IsArray() || !indicesArray.IsArray())
        {
            return false;
        }

        for (const auto& point : pointsArray.GetArray())
        {
            data.m_points.emplace_back(
                point[0].GetFloat(),
                point[1].GetFloat(),
                point[2].GetFloat(),
                point[3].GetFloat(),
                point[4].GetFloat()
            );
        }

        for (const auto& index : indicesArray.GetArray())
        {
            if (!index.IsInt())
            {
                return false;
            }

            data.m_indices.push_back(index.GetInt());
        }

        if (value.HasMember("color"))
        {
            const rapidjson::Value& color = value["color"];

            if (!color.IsArray() || color.Size() != 4)
            {
                return false;
            }

            data.m_color = Color(
                color[0].GetFloat(),
                color[1].GetFloat(),
                color[2].GetFloat(),
                color[3].GetFloat()
            );
        }

        if (value.HasMember("textureFileName"))
        {
            std::string textureName = value["textureFileName"].GetString();

            data.m_texture = ResourceManager::ResManager().GetWithID<Texture>(textureName, textureName, STR_Engine::m_renderer);
        }

        return true;
    }
}