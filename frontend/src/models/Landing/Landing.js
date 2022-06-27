import "./Landing.css";

export default function Landing() {
  return (
    <div className="pt-16 h-screen">
      <header className="image bg-cover h-full">
        <div className="content px-8 py-2">
          <div className="body mt-20 mx-8">
            <div className="md:flex items-center justify-between">
              <div className=" mt-40 w-full md:w-1/2 mr-auto">
                <h1 className="text-4xl sm:text-5xl font-bold text-white tracking-wide mb-2">
                  Computational Mind
                </h1>
                <h2 className="text-2xl sm:text-3xl font-bold text-white tracking-wide">
                  Welcome <span class="text-gray-800"> Aboard</span>
                </h2>
                <p className="text-gray-300  sm:text-lg">
                  Play or create problems/chalenges to improve Computational
                  Thinking.
                </p>
                <span className="text-white sm:text-lg flex flex-col">
                  Don't have an Account?
                  <a href="/SignUp" class="text-gray-900 sm:text-xl font-bold">
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
