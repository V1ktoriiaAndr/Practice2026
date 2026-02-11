#pragma once

#using <System.dll>
#using <System.Data.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

public ref class DbManager {
private:
    String^ connStr = "server=localhost;port=3306;user=root;password=Pentiuma5!;database=computer_shop";
    MySqlConnection^ conn;
public:
    DbManager() { conn = gcnew MySqlConnection(connStr); }

    bool Login(String^ user, String^ pass) {
        String^ query = "SELECT COUNT(*) FROM users WHERE username=@u AND password=@p";
        MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
        cmd->Parameters->AddWithValue("@u", user);
        cmd->Parameters->AddWithValue("@p", pass);
        conn->Open();
        int count = Convert::ToInt32(cmd->ExecuteScalar());
        conn->Close();
        return count > 0;
    }

    DataTable^ GetAll() {
        DataTable^ dt = gcnew DataTable();
        MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter("SELECT * FROM computers", conn);
        adapter->Fill(dt);
        return dt;
    }

    DataTable^ Search(String^ term) {
        DataTable^ dt = gcnew DataTable();
        String^ query = "SELECT * FROM computers WHERE pc_name LIKE @t OR cpu_type LIKE @t";
        MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
        cmd->Parameters->AddWithValue("@t", "%" + term + "%");
        MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
        adapter->Fill(dt);
        return dt;
    }

    void Add(String^ name, String^ cpu, double speed, int ram, int hdd, String^ video, String^ sound) {
        String^ query = "INSERT INTO computers (pc_name, cpu_type, clock_speed, ram_size, hdd_size, video_card, sound_card) VALUES (@n, @c, @s, @r, @h, @v, @sc)";
        MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);

        cmd->Parameters->AddWithValue("@n", name);
        cmd->Parameters->AddWithValue("@c", cpu);
        cmd->Parameters->AddWithValue("@s", speed);
        cmd->Parameters->AddWithValue("@r", ram);
        cmd->Parameters->AddWithValue("@h", hdd);
        cmd->Parameters->AddWithValue("@v", video);
        cmd->Parameters->AddWithValue("@sc", sound);

        try {
            conn->Open();
            cmd->ExecuteNonQuery();
            conn->Close();
        }
        catch (Exception^ ex) {
            if (conn->State == ConnectionState::Open) conn->Close();
            throw ex;
        }
    }

    void Delete(int id) {
        String^ query = "DELETE FROM computers WHERE id = @id";
        MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
        cmd->Parameters->AddWithValue("@id", id);

        try {
            conn->Open();
            cmd->ExecuteNonQuery();
            conn->Close();
        }
        catch (Exception^ ex) {
            if (conn->State == ConnectionState::Open) conn->Close();
            throw ex;
        }
    }

    void Update(int id, String^ name, String^ cpu, double speed, int ram, int hdd, String^ video, String^ sound) {
        String^ query = "UPDATE computers SET pc_name=@n, cpu_type=@c, clock_speed=@s, ram_size=@r, hdd_size=@h, video_card=@v, sound_card=@sc WHERE id=@id";
        MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);

        cmd->Parameters->AddWithValue("@n", name);
        cmd->Parameters->AddWithValue("@c", cpu);
        cmd->Parameters->AddWithValue("@s", speed);
        cmd->Parameters->AddWithValue("@r", ram);
        cmd->Parameters->AddWithValue("@h", hdd);
        cmd->Parameters->AddWithValue("@v", video);
        cmd->Parameters->AddWithValue("@sc", sound);
        cmd->Parameters->AddWithValue("@id", id);

        try {
            conn->Open();
            cmd->ExecuteNonQuery();
            conn->Close();
        }
        catch (Exception^ ex) {
            if (conn->State == ConnectionState::Open) conn->Close();
            throw ex;
        }
    }
};