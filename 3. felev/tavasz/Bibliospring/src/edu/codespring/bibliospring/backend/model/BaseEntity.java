package edu.codespring.bibliospring.backend.model;

public abstract class BaseEntity extends AbstractModel{
    private Long id;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }
}
