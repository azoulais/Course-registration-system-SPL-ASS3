package bgu.spl.net.impl.BGRSServer.DatabaseObjects;

import bgu.spl.net.impl.BGRSServer.Database;

public class Admin implements User {
    private String username;
    private String password;

    public Admin(String username, String password) {
        this.username = username;
        this.password = password;
    }

    public String getPassword(){return password;}
    public String getUsername(){return username;}

    @Override
    public String getCourseStatus(short courseNumber) {
        return Database.getInstance().getCourseStatus(courseNumber);
    }

    @Override
    public String getStudentStatus(String username) {
        User toGet = Database.getInstance().getUser(username);
        if(toGet == null)
            return null;
        return toGet.getStatus();
    }

}
