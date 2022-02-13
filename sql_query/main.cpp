#include <iostream>
#include <string>

#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

//exec command taken from https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

class SQLQuery {
    public:
    SQLQuery() = default;
    SQLQuery& Create() {
        query_ += "CREATE ";
        return *this;
    }
    SQLQuery& Show() {
        query_ += "SHOW ";
        return *this;
    }
    SQLQuery& Databases() {
        query_ += "DATABASES ";
        return *this;
    }
    SQLQuery& Database(const std::string& database_name) {
        query_ += "DATABASE " + database_name;
        return *this;
    }
    SQLQuery& Drop() {
        query_ += "DROP ";
        return *this;
    }
    const std::string& ToString() const {
        return query_;
    }
    private:
    std::string query_ {};
};

class SQL {
    public:
    SQL(const std::string& user, const std::string& password) : user_{user}, password_{password} {}
    void RunQuery(const SQLQuery& sql_query) {
        const std::string all = std::string{"mysql -u "} + user_ + std::string{" -p"} + password_ + std::string{" -e \""} + sql_query.ToString() + std::string{"\";"};
        auto output = exec(all.c_str());
        std::cout << output;
    }
    private:
    std::string user_ {};
    std::string password_{};
};





int main() {
    SQL sql{"testcpp","cpp"};
    sql.RunQuery(SQLQuery().Show().Databases());
    sql.RunQuery(SQLQuery().Create().Database("cpp_test_database"));
    sql.RunQuery(SQLQuery().Show().Databases());
    sql.RunQuery(SQLQuery().Drop().Database("cpp_test_database"));
    sql.RunQuery(SQLQuery().Show().Databases());
}