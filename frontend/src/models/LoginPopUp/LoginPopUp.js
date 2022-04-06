import { React } from "react";

import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faXmark } from "@fortawesome/free-solid-svg-icons";

export default function LoginPopUp({ setPopUp }) {
  return (
    <div className="flex justify-center items-center h-screen">
      <div
        className="absolute top-0 right-0 bottom-0 left-0 bg-slate-700 opacity-50 "
        onClick={setPopUp}
      ></div>

      <div className="w-[520px] h-[410px] border-2 border-color5 bg-white z-50 flex opacity-100 rounded-md flex-col">
        <FontAwesomeIcon
          icon={faXmark}
          className="text-3xl self-end mr-2 cursor-pointer hover:text-color5 duration-100"
        />
        <button className="flex items-center justify-center px-5 h-10 w-96 hover:bg-color1 border border-color1 rounded cursor-pointer duration-700 my-6 self-center">
          Player Login
        </button>
        <button className="flex items-center justify-center px-5 h-10 w-96 hover:bg-color4 border border-color4 rounded cursor-pointer duration-700 self-center">
          Author Login
        </button>
        <div className="w-full text-center my-5">______________________</div>
        <div className="w-full text-center">Don't have an account?</div>
        <div className="w-full text-center mt-5 cursor-pointer hover:text-color5 duration-100">
          Create an account now!
        </div>
      </div>
    </div>
  );
}
