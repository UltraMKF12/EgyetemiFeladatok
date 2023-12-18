package edu.codespring.bibliospring.backend.repository;

import edu.codespring.bibliospring.backend.repository.memory.MemoryDaoFactory;

public abstract class DaoFactory {
    public abstract UserDao getUserDao();
    public static DaoFactory getInstance() {
        return new MemoryDaoFactory();
    }
}
