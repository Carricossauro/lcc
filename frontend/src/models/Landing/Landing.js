import "./Landing.css";

export default function Landing() {
    return (
        <div className="pt-16 h-screen">
            <header className="image bg-cover h-full">
                <div className="content px-8 py-2">
                    <div className="body mt-20 mx-8">
                        <div className="md:flex items-center justify-between">
                            <div className=" mt-40 w-full md:w-1/2 mr-auto">
                                <h1 className="text-5xl font-bold text-white tracking-wide">
                                    Computational Mind
                                </h1>
                                <h2 className=" text-3xl font-bold text-white tracking-wide">
                                    Welcome{" "}
                                    <span className="text-gray-800">
                                        {" "}
                                        Aboard
                                    </span>
                                </h2>
                                <p className="text-gray-300 text-lg">
                                    Play or create problems/chalenges to improve
                                    Computational Thinking.
                                </p>
                                <span className="text-white text-lg">
                                    Don't have an Account?
                                    <a
                                        href="/SignUp"
                                        className="text-gray-900 text-xl ml-2 font-bold"
                                    >
                                        Register here.
                                    </a>
                                </span>
                            </div>
                        </div>
                    </div>
                </div>
            </header>
        </div>
    );
}
