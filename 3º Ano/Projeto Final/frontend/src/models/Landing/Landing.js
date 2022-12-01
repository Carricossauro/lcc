import "./Landing.css";
import brain from "../../assets/brain.svg";

export default function Landing() {
  return (
    <div className="pt-16 h-screen">
      <header className=" bg-gray-50 bg-cover h-full">
        <div className="content px-8 py-2">
          <div className="body mt-20 mx-8">
            <div className="md:flex md:flex-row flex-col items-center">
              <div className=" w-full md:min-w-[120px]">
                <h1 className="text-4xl sm:text-5xl font-bold text-color1 tracking-wide mb-2">
                  Computational Mind
                </h1>
                <h2 className="text-2xl sm:text-3xl font-bold text-color4 tracking-wide">
                  Welcome <span className="text-color1"> Aboard</span>
                </h2>
                <p className="text-color5  sm:text-lg">
                  Play or create problems/chalenges to improve Computational
                  Thinking.
                </p>
                <span className="text-color4 sm:text-lg flex flex-col">
                  Don't have an Account?
                  <a
                    href="/SignUp"
                    className="text-color5 sm:text-xl font-bold"
                  >
                    Register here.
                  </a>
                </span>
              </div>
              <div class="flex items-center w-full justify-center p-0 md:p-6 mt-10 md:mt-0">
                <img src={brain} alt="brain" className="max-w-[420px]" />
              </div>
            </div>
          </div>
        </div>
      </header>
    </div>
  );
}
