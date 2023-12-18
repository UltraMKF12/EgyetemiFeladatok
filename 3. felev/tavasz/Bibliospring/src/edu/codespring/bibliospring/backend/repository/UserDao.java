package edu.codespring.bibliospring.backend.repository;

import edu.codespring.bibliospring.backend.model.User;

import java.util.List;

public interface UserDao {
    public User create(User user);
    public User findById(Long id);
    public List<User> findAll();
}
