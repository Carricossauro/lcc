import React from "react";
import "./NavBar.css";

import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faBrain } from "@fortawesome/free-solid-svg-icons";

export default function NavBar() {
    return (
        <div className="fixed top-0 left-0 h-32 md:h-16 w-screen bg-color5 flex flex-wrap text-white">
            <div className="w-full md:w-2/5 h-inherit flex items-center pl-2">
                <FontAwesomeIcon icon={faBrain} className=" icon" />
                <span className="ml-2 text-[30px] titleFont font-normal">
                    Computational Mind
                </span>
            </div>
            <div className="w-full md:w-3/5 h-inherit flex flex-wrap justify-end items-center">
                <div className="w-1/6 flex justify-center">
                    <button className="flex items-center justify-center px-5 h-9 hover:bg-color1 rounded cursor-pointer duration-1000">
                        ABOUT US
                    </button>
                </div>
                <div className="w-1/6 flex justify-center">
                    <button className="flex items-center justify-center px-5 h-9 hover:bg-color1 rounded cursor-pointer duration-1000">
                        CONTACT
                    </button>
                </div>
                <div className="w-1/6 flex justify-center">
                    <button className="flex items-center justify-center px-5 h-9 hover:bg-color1 rounded cursor-pointer duration-1000">
                        SIGN UP
                    </button>
                </div>
                <div className="w-1/6 flex justify-center">
                    <button className="flex items-center justify-center px-5 h-9 bg-color1 rounded cursor-pointer hover:text-color4 hover:font-bold duration-1000">
                        LOGIN
                    </button>
                </div>
            </div>
        </div>
    );
}
