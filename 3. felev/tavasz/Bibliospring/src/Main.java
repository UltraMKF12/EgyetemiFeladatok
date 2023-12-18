import edu.codespring.bibliospring.backend.model.User;
import edu.codespring.bibliospring.backend.repository.DaoFactory;
import edu.codespring.bibliospring.backend.repository.UserDao;

public class Main {
    public static void main(String[] args) {
        User user = new User();
        user.setUserName("KrokodilEmber67");
        user.setPassword("viziloVaDaSz3311");
        DaoFactory daoFactory = DaoFactory.getInstance();
        UserDao userDao = daoFactory.getUserDao();
        System.out.println(userDao.create(user));
        System.out.println(userDao.findById(1L));

        User user2 = new User();
        user2.setUserName("Hagymacha");
        user2.setPassword("opoRopo5GO");
        userDao.create(user2);

        System.out.println(userDao.findAll());
    }
}