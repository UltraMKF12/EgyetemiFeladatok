package edu.codespring.bibliospring.backend.repository.memory;

import edu.codespring.bibliospring.backend.model.User;
import edu.codespring.bibliospring.backend.repository.UserDao;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicLong;

public class MemoryUserDao implements UserDao {
    private Map<Long, User> users;
    private AtomicLong generator;

    public MemoryUserDao() {
        generator = new AtomicLong();
        users = new ConcurrentHashMap<>();
    }

    @Override
    public User create(User user) {
        Long generatedId = generator.incrementAndGet();
        user.setId(generatedId);
        user.getUuid();
        users.put(generatedId, user);
        return user;
    }

    @Override
    public User findById(Long id) {
        return users.get(id);
    }

    @Override
    public List<User> findAll() {
        return new ArrayList<>(users.values());
    }
}
