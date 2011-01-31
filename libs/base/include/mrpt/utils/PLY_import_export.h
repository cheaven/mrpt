/* +---------------------------------------------------------------------------+
   |          The Mobile Robot Programming Toolkit (MRPT) C++ library          |
   |                                                                           |
   |                   http://mrpt.sourceforge.net/                            |
   |                                                                           |
   |   Copyright (C) 2005-2011  University of Malaga                           |
   |                                                                           |
   |    This software was written by the Machine Perception and Intelligent    |
   |      Robotics Lab, University of Malaga (Spain).                          |
   |    Contact: Jose-Luis Blanco  <jlblanco@ctima.uma.es>                     |
   |                                                                           |
   |  This file is part of the MRPT project.                                   |
   |                                                                           |
   |     MRPT is free software: you can redistribute it and/or modify          |
   |     it under the terms of the GNU General Public License as published by  |
   |     the Free Software Foundation, either version 3 of the License, or     |
   |     (at your option) any later version.                                   |
   |                                                                           |
   |   MRPT is distributed in the hope that it will be useful,                 |
   |     but WITHOUT ANY WARRANTY; without even the implied warranty of        |
   |     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
   |     GNU General Public License for more details.                          |
   |                                                                           |
   |     You should have received a copy of the GNU General Public License     |
   |     along with MRPT.  If not, see <http://www.gnu.org/licenses/>.         |
   |                                                                           |
   +---------------------------------------------------------------------------+ */
#ifndef  PLY_IMPORT_EXPORT_H
#define  PLY_IMPORT_EXPORT_H

#include <mrpt/utils/utils_defs.h>
#include <mrpt/utils/CStringList.h>

namespace mrpt
{
	namespace utils
	{
		/** A virtual base class that implements the capability of importing 3D point clouds and faces from a file in the Stanford PLY format.
		  * \sa http://www.mrpt.org/Support_for_the_Stanford_3D_models_file_format_PLY
		  * \sa PLY_Exporter
		  */
		class BASE_IMPEXP PLY_Importer
		{
		public:
			/** Loads from a PLY file.
			  * \param[in]  filename The filename to open. It can be either in binary or text format.
			  * \param[out] file_comments If provided (!=NULL) the list of comment strings stored in the file will be returned.
			  * \param[out] file_obj_info If provided (!=NULL) the list of "object info" strings stored in the file will be returned.
			  * \return false on any error in the file format or reading it. To obtain more details on the error you can call getLoadPLYErrorString()
			  */
			bool loadFromPlyFile(
				const std::string         &filename, 
				CStringList  *file_comments = NULL,
				CStringList  *file_obj_info = NULL );

			/** Return a description of the error if loadFromPlyFile() returned false, or an empty string if the file was loaded without problems. */
			std::string getLoadPLYErrorString() const { return m_ply_import_last_error; } 

		protected:
			/** @name PLY Import virtual methods to implement in base classes
			    @{ */

			/** In a base class, reserve memory to prepare subsequent calls to PLY_import_set_vertex */
			virtual void PLY_import_set_vertex_count(const size_t N) = 0;

			/** In a base class, reserve memory to prepare subsequent calls to PLY_import_set_face */
			virtual void PLY_import_set_face_count(const size_t N) = 0;

			/** In a base class, will be called after PLY_import_set_vertex_count() once for each loaded point. 
			  *  \param pt_color Will be NULL if the loaded file does not provide color info.
			  */
			virtual void PLY_import_set_vertex(const size_t idx, const mrpt::math::TPoint3Df &pt, const mrpt::utils::TColorf *pt_color = NULL) = 0;

			/** @} */

		private:
			std::string  m_ply_import_last_error;

		}; // End of class def.


		/** A virtual base class that implements the capability of exporting 3D point clouds and faces to a file in the Stanford PLY format.
		  * \sa http://www.mrpt.org/Support_for_the_Stanford_3D_models_file_format_PLY
		  * \sa PLY_Importer
		  */
		class BASE_IMPEXP PLY_Exporter
		{
		public:
			/** Saves to a PLY file.
			  * \param[in]  filename The filename to be saved.
			  * \param[in] file_comments If provided (!=NULL) the list of comment strings stored in the file will be returned.
			  * \param[in] file_obj_info If provided (!=NULL) the list of "object info" strings stored in the file will be returned.
			  * \return false on any error writing the file. To obtain more details on the error you can call getSavePLYErrorString()
			  */
			bool saveToPlyFile(
				const std::string  & filename, 
				bool save_in_binary = false,
				const CStringList  & file_comments = CStringList(),
				const CStringList  & file_obj_info = CStringList() ) const;

			/** Return a description of the error if loadFromPlyFile() returned false, or an empty string if the file was loaded without problems. */
			std::string getSavePLYErrorString() const { return m_ply_export_last_error; } 

		protected:
			/** @name PLY Export virtual methods to implement in base classes
			    @{ */

			/** In a base class, return the number of vertices */
			virtual size_t PLY_export_get_vertex_count() const = 0;

			/** In a base class, return the number of faces */
			virtual size_t PLY_export_get_face_count() const = 0;

			/** In a base class, will be called after PLY_export_get_vertex_count() once for each exported point. 
			  *  \param pt_color Will be NULL if the loaded file does not provide color info.
			  */
			virtual void PLY_export_get_vertex(
				const size_t idx, 
				mrpt::math::TPoint3Df &pt, 
				bool &pt_has_color,
				mrpt::utils::TColorf &pt_color) const = 0;

			/** @} */

		private:
			mutable std::string  m_ply_export_last_error;

		}; // End of class def.

	} // End of namespace
} // end of namespace
#endif