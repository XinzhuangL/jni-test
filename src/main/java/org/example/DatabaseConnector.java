package org.example;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class DatabaseConnector {

    public static String queryDatabase() {
        StringBuilder result = new StringBuilder();
        try {
            // load driver
            Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
            // create connection
            try (Connection conn = DriverManager.getConnection(
                    "jdbc:sqlserver://127.0.0.1:1433;databaseName=MyDatabase;trustServerCertificate=true",
                    "sa",
                    "Lxz74321.!"
            )) {
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery("select * from dbo.SampleTypeTable");
                int ct = rs.getMetaData().getColumnCount();
                while (rs.next()) {
                    for(int i = 1; i <= ct ; i++) {
                        result.append(rs.getString(i)).append(", ");
                    }
                    result.append("\n");
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
            return "Error: " + e.getMessage();
        }
        return result.toString();
    }
}
