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
class TT{
public:
    int ts;
    Tweet tweet;
    TT(int t,Tweet tw):ts(t),tweet(tw){}
    bool operator < (const TT &rhs) const{
        return ts < rhs.ts;
    }
};
class MiniTwitter {
private:
    unordered_map<int,unordered_set<int>> m_uid2friend;
    unordered_map<int,vector<TT>> m_uid2tweets;

    int timestamp;
public:
    MiniTwitter() {
        timestamp=0;
        m_uid2tweets.clear();
        m_uid2friend.clear();
    }

    // @param user_id an integer
    // @param tweet a string
    // return a tweet
    Tweet postTweet(int uid, string tweet_text) {
        // pull module
        // init tweet and its container
        Tweet t = Tweet::create(uid,tweet_text);
        TT t2 = TT(timestamp,t);
        timestamp+=1;
        // push to self timeline 
        m_uid2tweets[uid].push_back(t2);
        

        return t;
    }

    // @param user_id an integer
    // return a list of 10 new feeds recently
    // and sort by timeline
    vector<Tweet> getNewsFeed(int uid) {
        
        vector<Tweet> res;
        vector<TT> tmp = getRecent(m_uid2tweets[uid]);

        // find friends' tweets
        for(int id:m_uid2friend[uid]){
            
            vector<TT> tmp2 = getRecent(m_uid2tweets[id]);
            for(TT t: tmp2) tmp.push_back(t);
        }
        // our bool operator < should return ts<rhs.ts since we
        // are going to sort it from old -> new and
        // fetch from the bottom
        sort(tmp.begin(),tmp.end());
        vector<TT> tmp3 = getRecent(tmp);
        for(TT t: tmp3){
            res.push_back(t.tweet);
        }
           
        return res;
    }
        
    // @param user_id an integer
    // return a list of 10 new posts recently
    // and sort by timeline
    vector<Tweet>  getTimeline(int uid) {
        // self timeline is always in order
        vector<Tweet> res;
        vector<TT> tmp = getRecent(m_uid2tweets[uid]);
        
        for(TT t: tmp){
            res.push_back(t.tweet);
        }
        return res;
    }

    // @param from_user_id an integer
    // @param to_user_id an integer
    // from user_id follows to_user_id
    void follow(int from_id, int to_id) {
        m_uid2friend[from_id].insert(to_id);
    }

    // @param from_user_id an integer
    // @param to_user_id an integer
    // from user_id unfollows to_user_id
    void unfollow(int from_id, int to_id) {
        m_uid2friend[from_id].erase(to_id);
    }

    vector<TT> getRecent(vector<TT> &v){
        vector<TT> res;

        int len = v.size();
        for(int i=0; i<10 && i<len;++i){

            res.push_back(v[len-1-i]);
        }
        return res;
    }
};