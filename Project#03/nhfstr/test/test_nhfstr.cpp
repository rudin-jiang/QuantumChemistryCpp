#include <gtest/gtest.h>
#include "nhfstr.hpp"
#include <vector>
#include <string>
#include <cstddef>

TEST(TestNhfStr, TestRemoveComment) {
    std::vector<std::string> lines = {"", " ", "a", "aa", "bbb", "abcd"};

    for (const std::string &str1 : lines) {
    for (const std::string &str2 : lines) {
    for (const std::string &str3 : lines) {
        std::string words0;
        std::string words1 = str1;
        std::string words2 = str1 + str2;
        std::string words3 = str1 + str2 + str3;
        std::string line0 = words0 + "!" + str1 + str2 + str3;
        std::string line1 = words1 + "!" + str2 + str3;
        std::string line2 = words2 + "!" + str3;
        std::string line3 = words3 + "!";
        std::string line0m = words0 + "!" + str1 + "!" + str2 + "!" + str3;
        std::string line1m = words1 + "!" + str2 + "!" + str3;
        std::string line2m = words2 + "!" + str3;
        std::string line3m = words3 + "!";

        nhfStr::remove_comment(line0);
        nhfStr::remove_comment(line1);
        nhfStr::remove_comment(line2);
        nhfStr::remove_comment(line3);
        nhfStr::remove_comment(line0m);
        nhfStr::remove_comment(line1m);
        nhfStr::remove_comment(line2m);
        nhfStr::remove_comment(line3m);

        EXPECT_TRUE(line0 == words0);
        EXPECT_TRUE(line1 == words1);
        EXPECT_TRUE(line2 == words2);
        EXPECT_TRUE(line3 == words3);
        EXPECT_TRUE(line0m == words0);
        EXPECT_TRUE(line1m == words1);
        EXPECT_TRUE(line2m == words2);
        EXPECT_TRUE(line3m == words3);
    }}}
}

TEST(TestNhfStr, TestRemoveHeadSpace) {
    std::vector<std::string> space = {" ", "\f", "\n", "\r", "\t", "\v"};
    std::vector<std::string> lines = {
        "", "a", "aaa", "aaa aaa", "aaa\taaa"
    };

    std::string line;
    for (const std::string &s1 : space) {
    for (const std::string &s2 : space) {
        for (const std::string &l : lines) {
            // null space
            line = l;
            nhfStr::remove_head_space(line);
            EXPECT_TRUE(line == l);

            // one head space
            line = s1 + l;
            nhfStr::remove_head_space(line);
            EXPECT_TRUE(line == l);

            // two head space
            line = s1 + s2 + l;
            nhfStr::remove_head_space(line);
            EXPECT_TRUE(line == l);

            // one head space and one tail space
            line = s1 + l + s2;
            nhfStr::remove_head_space(line);
            if (l.empty()) {
                EXPECT_TRUE(line.empty());
            }
            else {
                EXPECT_TRUE(line == l + s2);
            }  
        }
    }}
}

TEST(TestNhfStr, TestRemoveTailSpace) {
    std::vector<std::string> space = {" ", "\f", "\n", "\r", "\t", "\v"};
    std::vector<std::string> lines = {
        "", "a", "aaa", "aaa aaa", "aaa\taaa"
    };

    std::string line;
    for (const std::string &s1 : space) {
    for (const std::string &s2 : space) {
        for (const std::string &l : lines) {
            // null space
            line = l;
            nhfStr::remove_tail_space(line);
            EXPECT_TRUE(line == l);

            // one tail space
            line = l + s1;
            nhfStr::remove_tail_space(line);
            EXPECT_TRUE(line == l);

            // two tail space
            line = l + s1 + s2;
            nhfStr::remove_tail_space(line);
            EXPECT_TRUE(line == l);

            // one head space and one tail space
            line = s1 + l + s2;
            nhfStr::remove_tail_space(line);
            if (l.empty()) {
                EXPECT_TRUE(line.empty());
            }
            else {
                EXPECT_TRUE(line == s1 + l);
            }  
        }
    }}
}

TEST(TestNhfStr, TestRemoveDualSpace) {
    std::vector<std::string> space = {" ", "\f", "\n", "\r", "\t", "\v"};
    std::vector<std::string> lines = {
        "", "a", "aaa", "aaa aaa", "aaa\taaa"
    };

    std::string line;
    for (const std::string &s1 : space) {
    for (const std::string &s2 : space) {
        for (const std::string &l : lines) {
            // null space
            line = l;
            nhfStr::remove_dual_space(line);
            EXPECT_TRUE(line == l);

            // one head space
            line = s1 + l;
            nhfStr::remove_dual_space(line);
            EXPECT_TRUE(line == l);

            // one tail space
            line = l + s1;
            nhfStr::remove_dual_space(line);
            EXPECT_TRUE(line == l);

            // two head space
            line = s1 + s2 + l;
            nhfStr::remove_dual_space(line);
            EXPECT_TRUE(line == l);

            // two tail space
            line = l + s1 + s2;
            nhfStr::remove_dual_space(line);
            EXPECT_TRUE(line == l);

            // one head space and one tail space
            line = s1 + l + s2;
            nhfStr::remove_dual_space(line);
            EXPECT_TRUE(line == l);
        }
    }}
}

TEST(TestNhfStr, TestStrUpper) {
    std::string line = "wsdgASDFGwgesrt03465343!@$##@%";
    std::string lineCopy = line;
    nhfStr::str_upper(line);
    for (std::size_t i = 0; i < line.size(); ++i) {
        if (lineCopy[i] >= 'a' && lineCopy[i] <= 'z') {
            EXPECT_TRUE(line[i] == lineCopy[i] - ('a' - 'A'));
        }
        else {
            EXPECT_TRUE(line[i] == lineCopy[i]);
        }
    }
}

TEST(TestNhfStr, TestStrLower) {
    std::string line = "wsdgASDFGwgesrt03465343!@$##@%";
    std::string lineCopy = line;
    nhfStr::str_lower(line);
    for (std::size_t i = 0; i < line.size(); ++i) {
        if (lineCopy[i] >= 'A' && lineCopy[i] <= 'Z') {
            EXPECT_TRUE(line[i] == lineCopy[i] + ('a' - 'A'));
        }
        else {
            EXPECT_TRUE(line[i] == lineCopy[i]);
        }
    }
}

TEST(TestNhfStr, TestStrChange) {
    std::string line = "wsdgASDFGwgesrt03465343!@$##@%";
    std::string pre = "abcdefghijklmnopqrstuvwxyz0123456789";
    std::string aft = "abcdefghijklmnopqrstuvwxyz0123456789";

    for (std::size_t i = 0; i < pre.size(); ++i) {
    for (std::size_t j = 0; j < aft.size(); ++j) {
        std::string tmp = line;
        nhfStr::str_change(tmp, pre[i], aft[j]);
        
        for (std::size_t k = 0; k < line.size(); ++k) {
            if (line[k] == pre[i]) {
                EXPECT_TRUE(tmp[k] == aft[j]);
            }
            else {
                EXPECT_TRUE(tmp[k] == line[k]);
            }
        }
    }}

}

TEST(TestNhfStr, TestSplitString) {
    std::vector<std::string> delms = {" ", ".", "..", "...", "!", "!!", "!!!"};
    std::vector<std::string> elems = {"a", "aa", "abc", "abcdef"};
    std::vector<std::string> ret;
    std::string line;

    for (const std::string &delm : delms) {
        // empty line
        line.clear();
        ret = nhfStr::split_string(line, delm);
        EXPECT_TRUE(ret.empty());

        // just one delimiter
        line = delm;
        ret = nhfStr::split_string(line, delm);
        EXPECT_TRUE(ret.empty());

        // just two delimiters
        line = delm + delm;
        ret = nhfStr::split_string(line, delm);
        EXPECT_TRUE(ret.empty());

        // just three delimiters
        line = delm + delm + delm;
        ret = nhfStr::split_string(line, delm);
        EXPECT_TRUE(ret.empty());

        // one element
        for (const std::string &elem : elems) {
            // without delimiters
            line = elem;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 1);
            EXPECT_TRUE(ret[0] == elem);

            // one element + one delimiter
            line = elem + delm;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 1);
            EXPECT_TRUE(ret[0] == elem);

            // one delimiter + one element
            line = delm + elem;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 1);
            EXPECT_TRUE(ret[0] == elem);

            // delm delm elem
            line = delm + delm + elem;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 1);
            EXPECT_TRUE(ret[0] == elem);

            // delm elem delm
            line = delm + elem + delm;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 1);
            EXPECT_TRUE(ret[0] == elem);

            // elem delm delm
            line = elem + delm + delm;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 1);
            EXPECT_TRUE(ret[0] == elem);
        }

        // two elements
        for (const std::string &elem1 : elems) {
        for (const std::string &elem2 : elems) {
            // elem1 delm elem2
            line = elem1 + delm + elem2;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 2);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);

            // elem1 delm delm elem2
            line = elem1 + delm + delm + elem2;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 2);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);

            // delm elem1 delm elem2
            line = delm + elem1 + delm + elem2;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 2);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);

            // elem1 delm elem2 delm     
            line = elem1 + delm + elem2 + delm;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 2);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);

            // delm elem1 delm elem2 delm
            line = delm + elem1 + delm + elem2 + delm;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 2);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);
        }}

        // three elements
        for (const std::string &elem1 : elems) {
        for (const std::string &elem2 : elems) {
        for (const std::string &elem3 : elems) {
            // elem1 delm elem2 delm elem3
            line = elem1 + delm + elem2 + delm + elem3;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 3);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);
            EXPECT_TRUE(ret[2] == elem3);

            // delm elem1 delm elem2 delm elem3
            line = delm + elem1 + delm + elem2 + delm + elem3;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 3);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);
            EXPECT_TRUE(ret[2] == elem3);

            // elem1 delm elem2 delm elem3 delm
            line = elem1 + delm + elem2 + delm + elem3 + delm;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 3);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);
            EXPECT_TRUE(ret[2] == elem3);

            // delm elem1 delm elem2 delm elem3 delm
            line = delm + elem1 + delm + elem2 + delm + elem3 + delm;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 3);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);
            EXPECT_TRUE(ret[2] == elem3);

            // elem1 delm delm elem2 delm elem3
            line = elem1 + delm + delm + elem2 + delm + elem3;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 3);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);
            EXPECT_TRUE(ret[2] == elem3);

            // elem1 delm elem2 delm delm elem3
            line = elem1 + delm + elem2 + delm + delm + elem3;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 3);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);
            EXPECT_TRUE(ret[2] == elem3);

            // delm delm elem1 delm elem2 delm elem3
            line = delm + delm + elem1 + delm + elem2 + delm + elem3;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 3);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);
            EXPECT_TRUE(ret[2] == elem3);

            // elem1 delm delm elem2 delm elem3
            line = elem1 + delm + delm + elem2 + delm + elem3;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 3);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);
            EXPECT_TRUE(ret[2] == elem3);

            // elem1 delm elem2 delm delm elem3
            line = elem1 + delm + elem2 + delm + delm + elem3;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 3);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);
            EXPECT_TRUE(ret[2] == elem3);

            // delm delm elem1 delm delm elem2 delm elem3
            line = delm + delm + elem1 + delm + delm + elem2 + delm + elem3;
            ret = nhfStr::split_string(line, delm);
            EXPECT_TRUE(ret.size() == 3);
            EXPECT_TRUE(ret[0] == elem1);
            EXPECT_TRUE(ret[1] == elem2);
            EXPECT_TRUE(ret[2] == elem3);
        }}}
    }
}