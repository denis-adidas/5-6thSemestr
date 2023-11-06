import com.google.gson.stream.JsonToken;
import org.junit.Before;
import org.junit.Test;
import org.suai.lab15.LoginServlet;
import org.suai.lab15.User;
import org.suai.lab15.UserManager;

import static org.junit.Assert.*;

public class UserManagerTest {
    private UserManager userManager;

    @Before
    public void setUp() {
        userManager = new UserManager();
        UserManager.loadFromJsonFile("autosave15.json");
    }

    @Test
    public void testAddUser() {
        User user = new User("TestUser", "111");
        userManager.addUser(user);
        assertNotNull(userManager.getUserByName("TestUser"));
    }

    @Test
    public void testGetUserByName() {
        User user1 = new User("User1", "1");
        User user2 = new User("User2", "111");
        userManager.addUser(user1);
        userManager.addUser(user2);
        assertEquals(user1, userManager.getUserByName("User1"));
        assertEquals(user2, userManager.getUserByName("User2"));
        assertNull(userManager.getUserByName("NonExistentUser"));
    }

    @Test
    public void testSaveAndLoadToJsonFile() {
        User user = new User("SavedUser", "111");
        userManager.addUser(user);
        userManager.saveToJsonFile("autosave.json");
        UserManager loadedManager = UserManager.loadFromJsonFile("autosave.json");
        User loadedUser = loadedManager.getUserByName("SavedUser");
        assertNotNull(loadedUser);
        assertEquals(user.getName(), loadedUser.getName());
    }
    @Test
    public void testCheckAuthenticatorValidUser() {
        LoginServlet ls = new LoginServlet();

        assertTrue(ls.checkAuthenticator("User1", "1"));
        assertTrue(ls.checkAuthenticator("User2", "2"));
        assertTrue(ls.checkAuthenticator("User11", "11"));
    }
    @Test
    public void testReturnUserParametrs() {
        LoginServlet ls = new LoginServlet();
        UserManager userManager = UserManager.loadFromJsonFile("autosave15.json");
        User user = userManager.getUserByName("User1");
        assertEquals("User5", user.getName());
        assertEquals("1", user.getPassword());
    }
}
