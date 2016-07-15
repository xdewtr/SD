/**
 * Definition of Tweet:
 * class Tweet {
 * public:
 *     int id;
 *     int user_id;
 *     String text;
 *     static Tweet create(int user_id, string tweet_text) {
 *         // This will create a new tweet object,
 *         // and auto fill id
 *     }
 * }
 */
class MiniTwitter {
private:
    unordered_map<int,unordered_set<int>> m_uid2followers;
    unordered_map<int,vector<Tweet>> m_uid2tweets;
    unordered_map<int,vector<Tweet>> m_uid2news;
public:
    MiniTwitter() {
        
        m_uid2news.clear();
        m_uid2tweets.clear();
        m_uid2followers.clear();
    }

    // @param user_id an integer
    // @param tweet a string
    // return a tweet
    Tweet postTweet(int uid, string tweet_text) {
        // push module
        Tweet t = Tweet::create(uid,tweet_text);
        m_uid2tweets[uid].push_back(t);
        m_uid2news[uid].push_back(t);
        for(int id:m_uid2followers[uid]){
            m_uid2news[id].push_back(t);
        }

        return t;
    }

    // @param user_id an integer
    // return a list of 10 new feeds recently
    // and sort by timeline
    vector<Tweet> getNewsFeed(int uid) {
        vector<Tweet> tmp = m_uid2news[uid];
        vector<Tweet> res;
        for(int i=0; i<10;++i){
            res.push_back(tmp[tmp.size()-1-i]);
        }
        return res;
    }
        
    // @param user_id an integer
    // return a list of 10 new posts recently
    // and sort by timeline
    vector<Tweet>  getTimeline(int uid) {
        vector<Tweet> tmp = m_uid2tweets[uid];
        vector<Tweet> res;
        for(int i=0; i<10;++i){
            res.push_back(tmp[tmp.size()-1-i]);
        }
        return res;
    }

    // @param from_user_id an integer
    // @param to_user_id an integer
    // from user_id follows to_user_id
    void follow(int from_id, int to_id) {
        m_uid2followers[to_id].insert(from_id);
    }

    // @param from_user_id an integer
    // @param to_user_id an integer
    // from user_id unfollows to_user_id
    void unfollow(int from_id, int to_id) {
        m_uid2followers[to_id].erase(from_id);
    }
};