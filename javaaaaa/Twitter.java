import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Set;
import java.util.List;

public class Twitter {

  private int timestamp = 0;

  private class Tweet {

    private int id;
    private int time;
    private Tweet next;

    public Tweet(int id, int time) {
      this.id = id;
      this.time = time;
      this.next = null;
    }
  }

  private class User {

    private int id;
    private Set<Integer> followed;
    private Tweet head;

    public User(int id) {
      this.id = id;
      followed = new HashSet<Integer>();
      this.head = null;
      followed.add(id);
    }

    public void follow(int userId) {
      followed.add(userId);
    }

    public void unFollow(int userId) {
      if (userId != this.id) followed.remove(userId);
    }

    public void post(int tweetId) {
      Tweet tweet = new Tweet(tweetId, timestamp);
      timestamp++;
      tweet.next = head;
      head = tweet; //头插
    }
  }

  HashMap<Integer, User> userMap = new HashMap<Integer, User>();

  public Twitter() {}

  public void postTweet(int userId, int tweetId) {
    if (!userMap.containsKey(userId)) {
      User user = new User(userId);
      userMap.put(userId, user);
    }
    User user = userMap.get(userId);
    user.post(tweetId);
  }

  public List<Integer> getNewsFeed(int userId) {
    ArrayList<Integer> result = new ArrayList<>();
    if (!userMap.containsKey(userId)) return result;
    Set<Integer> users = userMap.get(userId).followed;
    PriorityQueue<Tweet> priorityQueue = new PriorityQueue<>(
      (o1, o2) -> o2.time - o1.time
    );
    for (Integer id : users) {
      Tweet twt = userMap.get(id).head;
      if (twt == null) continue;
      priorityQueue.offer(twt);
    }
    while (!priorityQueue.isEmpty()) {
      if (result.size() == 10) break;
      Tweet twt = priorityQueue.poll();
      result.add(twt.id);
      if (twt.next != null) {
        priorityQueue.offer(twt.next);
      }
    }
    return result;
  }

  public void follow(int followerId, int followeeId) {
    if (!userMap.containsKey(followerId)) userMap.put(
      followerId,
      new User(followerId)
    );
    if (!userMap.containsKey(followeeId)) userMap.put(
      followeeId,
      new User(followeeId)
    );
    userMap.get(followerId).follow(followeeId);
  }

  public void unfollow(int followerId, int followeeId) {
    if (userMap.containsKey(followerId)) {
      userMap.get(followerId).unFollow(followeeId);
    }
  }
}
