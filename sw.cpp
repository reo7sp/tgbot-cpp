void build(Solution &s)
{
    auto &tgbot = s.addLibrary("reo7sp.tgbot", "1.2.1");
    tgbot += Git("https://github.com/reo7sp/tgbot-cpp", "v{M}.{m}");
    {
        tgbot += cpp11;

        tgbot.ApiName = "TGBOT_API";
        tgbot.Public += "org.sw.demo.boost.property_tree"_dep;
        tgbot.Public += "org.sw.demo.openssl.ssl"_dep;
        tgbot.Public += "org.sw.demo.boost.system"_dep;
        tgbot.Public += "org.sw.demo.boost.date_time"_dep;
        tgbot.Public += "org.sw.demo.badger.curl.libcurl"_dep, "HAVE_CURL"_def;
        tgbot.Public += "org.sw.demo.boost.asio"_dep;
    }

    auto &t = tgbot.addExecutable("test");
    {
        t.Scope = TargetScope::Test;
        t += cpp11;
        t += "test/.*"_rr;
        t += "test"_idir;
        t += "SW_BUILD"_def;
        t += tgbot;
        t += "org.sw.demo.boost.test"_dep;
    }

    tgbot.addTest(t);
}
