import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import {
  faAt,
  faLocationDot,
  faAddressCard,
  faEnvelope,
  faCalendar,
} from "@fortawesome/free-solid-svg-icons";

export default function Contact() {
  return (
    <div className="mt-32 flex items-center y-full px-8 sm:flex-row flex-col">
      <div className="flex flex-col lg:ml-20 mb-10 sm:items-start pr-0 sm:pr-4 w-full">
        <h1 className="text-5xl text-center sm:text-left font-bold tracking-wide text-color5 mb-8">
          Contact Us
        </h1>
        <span className="text-base sm:text-xl flex items-center mb-4 text-gray-700">
          <FontAwesomeIcon icon={faAt} className="text-lg sm:text-2xl w-8" />
          <p class="ml-2">computationalmind@di.uminho.pt</p>
        </span>
        <span className="text-base sm:text-xl flex text-gray-700">
          <FontAwesomeIcon
            icon={faLocationDot}
            className="text-lg sm:text-2xl w-8 "
          />
          <div className="flex flex-col">
            <p class="ml-2">
              Departamento de Informática - Universidade do Minho
            </p>
            <p class="ml-3">4710-057, Braga</p>
          </div>
        </span>
      </div>
      <form class="w-full sm:w-1/2 max-w-lg">
        <div class="flex flex-wrap -mx-3 mb-6">
          <div class="w-full md:w-1/2 px-3 mb-6 md:mb-0">
            <label
              class="block uppercase tracking-wide text-gray-700 text-xs font-bold mb-2"
              for="grid-first-name"
            >
              First Name
            </label>
            <input
              class="appearance-none block w-full bg-gray-200 text-gray-700 border border-red-500 rounded py-3 px-4 mb-3 leading-tight focus:outline-none focus:bg-white"
              id="grid-first-name"
              type="text"
              placeholder="Jane"
            />
            <p class="text-red-500 text-xs italic">
              Please fill out this field.
            </p>
          </div>
          <div class="w-full md:w-1/2 px-3">
            <label
              class="block uppercase tracking-wide text-gray-700 text-xs font-bold mb-2"
              for="grid-last-name"
            >
              Last Name
            </label>
            <input
              class="appearance-none block w-full bg-gray-200 text-gray-700 border border-gray-200 rounded py-3 px-4 leading-tight focus:outline-none focus:bg-white focus:border-gray-500"
              id="grid-last-name"
              type="text"
              placeholder="Doe"
            />
          </div>
        </div>
        <div class="flex flex-wrap -mx-3 mb-6">
          <div class="w-full px-3">
            <label
              class="block uppercase tracking-wide text-gray-700 text-xs font-bold mb-2"
              for="grid-password"
            >
              E-mail
            </label>
            <input
              class="appearance-none block w-full bg-gray-200 text-gray-700 border border-gray-200 rounded py-3 px-4 mb-3 leading-tight focus:outline-none focus:bg-white focus:border-gray-500"
              id="email"
              type="email"
            />
            <p class="text-gray-600 text-xs italic">
              Some tips - as long as needed
            </p>
          </div>
        </div>
        <div class="flex flex-wrap -mx-3 mb-6">
          <div class="w-full px-3">
            <label
              class="block uppercase tracking-wide text-gray-700 text-xs font-bold mb-2"
              for="grid-password"
            >
              Message
            </label>
            <textarea
              class=" no-resize appearance-none block w-full bg-gray-200 text-gray-700 border border-gray-200 rounded py-3 px-4 mb-3 leading-tight focus:outline-none focus:bg-white focus:border-gray-500 h-48 resize-none"
              id="message"
            ></textarea>
            <p class="text-gray-600 text-xs italic">
              Re-size can be disabled by set by resize-none / resize-y /
              resize-x / resize
            </p>
          </div>
        </div>
        <div class="md:flex md:items-center mb-10">
          <div class="md:w-1/3">
            <button
              class="shadow bg-color1 hover:bg-teal-400 focus:shadow-outline focus:outline-none text-white font-bold py-2 px-4 rounded"
              type="button"
            >
              Send
            </button>
          </div>
        </div>
      </form>
    </div>
  );
}
