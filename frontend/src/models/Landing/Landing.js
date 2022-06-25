import "./Landing.css";

export default function Landing() {
  return (
    <div className="pt-16 h-screen">
      <header className="image bg-cover h-full">
        <div className="content px-8 py-2">
          <div className="body mt-20 mx-8">
            <div className="md:flex items-center justify-between">
              <div className="shadow w-full md:w-1/2 mr-auto">
                <h1 className="text-4xl font-bold text-white tracking-wide">
                  Computational Mind
                </h1>
                <h2 className=" text-2xl font-bold text-white tracking-wide">
                  Welcome <span class="text-gray-800"> Aboard</span>
                </h2>
                <p className="text-gray-300">
                  Play or create problems/chalenges to improve Computational
                  Thinking.
                </p>
                <span className="text-white">
                  Create New Account?
                  <a href="#" class="text-gray-900 text-lg ml-2 font-bold">
                    Sign Up
                  </a>
                </span>
              </div>
              <div className="w-full md:max-w-md mt-6">
                <div className="card bg-white shadow-md rounded-lg px-4 py-4 mb-6 ">
                  {/* <form action="#">
                                <div className="flex items-center justify-center">
                                    <h2 className="text-2xl font-bold tracking-wide">
                                        Welcome back
                                    </h2> 
                                </div>
                                <h2 className="text-xl text-center font-semibold text-gray-800 mb-2">
                                    Sign In
                                </h2>
                                <input type="text"
                                 className="rounded px-4 w-full py-1 bg-gray-200  border border-gray-400 mb-6 text-gray-700 placeholder-gray-700 focus:bg-white focus:outline-none" placeholder="Email Address">
                                <input type="password" class="rounded px-4 w-full py-1 bg-gray-200  border border-gray-400 mb-4 text-gray-700 placeholder-gray-700 focus:bg-white focus:outline-none" placeholder="Password">
                                <div className="flex items-center justify-between">
                                    <a href="#" class="text-gray-600">Forget Password?</a>
                                    <button className="bg-gray-800 text-gray-200  px-2 py-1 rounded">Sign In</button>
                                </div>
                            </form> */}
                </div>
              </div>
            </div>
          </div>
        </div>
      </header>
    </div>
  );
}
