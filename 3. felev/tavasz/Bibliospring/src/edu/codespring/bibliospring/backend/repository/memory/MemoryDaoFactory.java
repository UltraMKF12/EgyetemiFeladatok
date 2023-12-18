package edu.codespring.bibliospring.backend.repository.memory;

import edu.codespring.bibliospring.backend.repository.DaoFactory;
import edu.codespring.bibliospring.backend.repository.UserDao;

public class MemoryDaoFactory extends DaoFactory {
    public UserDao getUserDao() {
        return new MemoryUserDao();
    }
}
