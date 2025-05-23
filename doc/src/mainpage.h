/**
 * @file mainpage.h 
 *
 * @copyright Copyright (c) 2024  Federal Office for Information Security, Germany
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @brief This header file is for generating the doxygen documentation
 * for OFIQ.
 * @author OFIQ development team
 *
 * @mainpage Open Source Face Image Quality (OFIQ) Library
 * @section sec_intro Introduction
 * OFIQ (Open Source Face Image Quality) is a software library for computing quality 
 * aspects of a facial image. OFIQ is written in the C/C++ programming language.
 * OFIQ is the reference implementation for the ISO/IEC 29794-5 international
 * standard; see [https://bsi.bund.de/dok/OFIQ-e](https://bsi.bund.de/dok/OFIQ-e).
 * 
 * @includedoc "../../LICENSE.md"
 * @includedoc "../../BUILD.md"
 * 
 * @section sec_config Configuration
 * In this section, we describe the configuration file for OFIQ.
 * OFIQ uses a JSON-like configuration based on the [taoJSON](https://github.com/taocpp/json) 
 * library. Using taoJSON, OFIQ reads its configuration from a
 * [JAXN](https://github.com/stand-art/jaxn)-formatted file.
 * <br/>
 * <br/>
 * A minimal configuration working with OFIQ looks as follows.
 * <pre>
{
 "config": {
  "detector": "ssd",
  "landmarks": "ADNet",
  "measures": [
   "UnifiedQualityScore"
  ],
  "params": {
   "detector": {
    "ssd": {
     "model_path": "models/face_detection/ssd_facedetect.caffemodel",
     "prototxt_path": "models/face_detection/ssd_facedetect.prototxt.txt",
     "confidence_thr": 0.4,
     "min_rel_face_size": 0.01,
     "padding": 0.2
    }
   },
   "landmarks": {
    "ADNet": {
     "model_path": "models/face_landmark_estimation/ADNet.onnx"
    }
   },
   "measures": {
    "UnifiedQualityScore": {
     "model_path": "models/unified_quality_score/magface_iresnet50_norm.onnx"
    },
    "HeadPose": {
     "model_path": "models/head_pose_estimation/mb1_120x120.onnx"
    },
    "FaceOcclusionSegmentation": {
     "model_path": "models/face_occlusion_segmentation/face_occlusion_segmentation_ort.onnx"
    },
    "FaceParsing": {
     "model_path": "models/face_parsing/bisenet_400.onnx"
    }
   }
  }
 }
}
 * </pre>
 * OFIQ's C/C++ library provides the class \link OFIQ_LIB::Configuration Configuration\endlink 
 * which is responsible for reading and managing JAXN configurations.
 * <br/><br/>
 * Note that the model paths are specified as paths relative to the directory of the 
 * JAXN configuration file. We assume that the file above is stored in <OFIQ-SOURCE>/data.
 * 
 * @subsection sec_facedetect_cfg Configuration of the face detector
 * The face detector (SSD) must
 * be configured explicitly:
 * <pre>
 * {
 *  "config": {
 *    "detector": "ssd",
 *    ...
 *  }
 * }
 * </pre>
 * Additionally, the path to the model file and other parameters need 
 * to be configured:
 * <pre>
 * {
 *  ...
 *    "params": {
 *     "detector": {
 *       "ssd": {
 *         "model_path": "models/face_detection/ssd_facedetect.caffemodel",
 *         "prototxt_path": "models/face_detection/ssd_facedetect.prototxt.txt",
 *         "confidence_thr": 0.4,
 *         "min_rel_face_size": 0.01,
 *         "padding": 0.2
 *       }
 *     },
    ...  
 * }
 * </pre>
 * A documentation on the parameters are given in the following table.
 * <table>
 *  <tr>
 *   <td><b>Parameter</b></td><td><b>Description</b></td> 
 *  </tr>
 *  <tr>
 *   <td>model_path</td><td>path to the SSD model file in CAFEE format</td> 
 *  </tr>
 *  <tr>
 *   <td>prototxt_path</td><td>path to SSD's CAFFE protype file</td> 
 *  </tr>
 *  <tr>
 *   <td>confidence_thr</td><td>minimum value for the confidence 
 *   the detected faces; detected faces with 
 *   a lower confidence are discarded. Note, the specified value 0.4 (fixed for OFIQ) has 
 *   been determined experimentally.</td> 
 *  </tr>
 *  <tr>
 *   <td>min_rel_face_size</td><td>the minimum width of the face 
 *   bounding boxes relative to the width w of the input image;
 *   detected faces, with a bounding box width smaller than 
 *   min_rel_face_size*w are discarded. Note, the specified value 0.01 (fixed for OFIQ) has 
 *   been determined experimentally.</td> 
 *  </tr>
 *  <tr>
 *   <td>padding</td><td>horizontal and vertical padding of the
 *   original image prior face detection. Note, the specified value 0.2 (fixed for OFIQ) has 
 *   been determined experimentally.</td> 
 *  </tr>
 * </table>
 * 
 * @subsection sec_facelandmark_cfg Configuration of the landmark extractor
 * The face landmark extractor (ADNet) must be configured explicitly:
 * <pre>
 * {
 *  "config": {
 *    ...
 *    "landmarks": "ADNet",
 *    ...
 *  }
 * }
 * </pre>
 * Additionally, the path to the ADNet model file in ONNX format needs 
 * to be configured:
 * <pre>
 * {
 *  ...
 *    "params": {
 *     ...
 *     "landmarks": {
 *       "ADNet": {
 *         "model_path": "models/face_landmark_estimation/ADNet.onnx"
 *       }
 *     },
 *  ...  
 * }
 * </pre>
 * 
 * @subsection sec_required_cfg Other required configurations
 * As suggested by the minimal configuration file given in @ref sec_config, there
 * are model files that need to be configured and their configurations cannot be omitted.
 * These model files are detailed in the following table and shall be configured in 
 * the "config"."measures" environment.
 * <table>
 *  <tr><td><b>Algorithm</b></td><td><b>Description</b></td></tr>
 *  <tr><td>\link OFIQ_LIB::modules::measures::HeadPose HeadPose\endlink</td>
 *  <td></td>Head pose angles are pre-processed and used by some measures;
 *  therefore, the measure shall be configured. The path to the 
 *  [3DDFAV2](https://github.com/cleardusk/3DDFA_V2) model file 
 *  in ONNX format should be set using the <code>model_path</code> key.</tr>
 *  <tr><td>\link OFIQ_LIB::modules::segmentations::FaceOcclusionSegmentation FaceOcclusionSegmentation\endlink</td>
 *  <td></td>Face occlusion segmentation pre-processing used by some measures assessing occlusion prevention. 
 *  The path to the  [FaceExtraction](https://github.com/face3d0725/FaceExtraction)
 *  model file in ONNX format should be set using the <code>model_path</code> key.
 *  NOTE: The OFIQ development team has been permitted by the FaceExtraction authors for 
 *  inclusion of the model in OFIQ without any restrictions; therefore, the referenced ONNX
 *  model file is subject to the OFIQ license agreement.</tr>
 *  <tr><td>\link OFIQ_LIB::modules::segmentations::FaceParsing FaceParsing\endlink</td>
 *   <td></td>Face parsing is pre-processed and used by some measures;
 *   therefore, the measure shall be configured (even if no measure is requested that uses
 *   the pre-processing result). The path to the 
 *   [BiSeNet](https://github.com/zllrunning/face-parsing.PyTorch) model file in ONNX format 
 *  should be set using the <code>model_path</code> key.</tr>
 * </table>
 * 
 * @subsection sec_requesting_measures Requesting measures
 * OFIQ implements a variety of measures for assessing properties of a facial
 * image. For a measure to be executed by OFIQ, it must be explicitly requested. 
 * For example, to only request the unified quality score measure, one can request it as follows.
 * <pre>
 * {
 *  "config": {
 *    ...
 *    "measures": [
 *     "UnifiedQualityScore"
 *    ],
 *    ...
 *  }
 * }
 * </pre>
 * At least one measure must be requested. An empty request list will
 * result in OFIQ throwing an error. A full list of requestable measures and its
 * <i>measure keys</i> can be found in the table of the 
 * @ref sec_default_config "default configuration section".
 * 
 * @subsection sec_default_config Default configuration
 * OFIQ is the reference implementation for the ISO/IEC 29794-5 standard. To reproduce the
 * conformance tests of the ISO/IEC 29794-5 standard one should use the (default) configuration provided
 * by the file <code><OFIQ-SOURCE>/data/ofiq_config.jaxn</code>; other configurations 
 * can be used; however, the resulting outputs of the quality assessment may not comply
 * with the ISO/IEC 29794-5 standard.
 * <br />
 * <br />
 * The entries of the default configuration are documented in the following table. 
 * Details on the algorithms can be found in the ISO/IEC 29794-5 document. Details on the 
 * implementations can be found in the OFIQ source code. Note, the QAA identifiers 
 * listed in the table are defined in ISO/IEC 29794-5.
 * 
 * <table>
 *  <tr>
 *  <td><b>QAA identifier</b></td>
 *  <td><b>description</b></td>
 *  <td><b>config key</b></td>
 *  <td><b>request key</b></td>
 *  <td><b>configuration parameters</b></td>
 *  <td><b>supports quality mapping config? - see details @ref sec_quality_config "here"</b></td>
 *  </tr>
 *  
 *  <tr>
 *  <td>-</td>
 *  <td>Face detector</td>
 *  <td>"config">"params".<br/>"detector"</td>
 *  <td>-</td>
 *  <td>see @ref sec_facedetect_cfg "here"</td>
 *  <td>-</td>
 *  </tr>
 *
 *  <tr>
 *  <td>-</td>
 *  <td>Face landmark estimator</td>
 *  <td>"config">"params".<br/>"landmarks"</td>
 *  <td>-</td>
 *  <td>see @ref sec_facelandmark_cfg "here"</td>
 *  <td>-</td>
 *  </tr>
 *
 *  <tr>
 *  <td>-</td>
 *  <td>Face parsing</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"FaceParsing"</td>
 *  <td>-</td>
 *  <td>see @ref sec_required_cfg "here"</td>
 *  <td>-</td>
 *  </tr> 
 *
 *  <tr>
 *  <td>-</td>
 *  <td>Face occlusion segmentation</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"FaceOcclusionSegmentation"</td>
 *  <td>-</td>
 *  <td>see @ref sec_required_cfg "here"</td>
 *  <td>-</td>
 *  </tr>
 *
 *  <tr>
 *  <td>-</td>
 *  <td>Landmarked region</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"FaceRegion"</td>
 *  <td>-</td>
 *  <td><code>alpha</code>: is 0 per default and only used for internal purposes</td>
 *  <td>-</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x41</td>
 *  <td>Unified quality score</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"UnifiedQualityScore"</td>
 *  <td>"config".<br/>"measures".<br/>"UnifiedQualityScore"</td>
 *  <td><code>model_path</code>: Path to an iResNet50 model file in ONNX format</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x42</td>
 *  <td>Background uniformity</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"BackgroundUniformity"</td>
 *  <td>"config".<br/>"measures".<br/>"BackgroundUniformity"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x43</td>
 *  <td>Illumination unformity</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"IlluminationUniformity"</td>
 *  <td>"config".<br/>"measures".<br/>"IlluminationUniformity"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x44</td>
 *  <td>Luminance brightness</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"Luminance"</td>
 *  <td>"config".<br/>"measures".<br/>"Luminance"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x45</td>
 *  <td>Luminance contrast</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"Luminance"</td>
 *  <td>"config".<br/>"measures".<br/>"Luminance"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x46</td>
 *  <td>Abscence of under-exposure</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"UnderExposurePrevention"</td>
 *  <td>"config".<br/>"measures".<br/>"UnderExposurePrevention"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x47</td>
 *  <td>Abscence of over-exposure</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"OverExposurePrevention"</td>
 *  <td>"config".<br/>"measures".<br/>"OverExposurePrevention"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x48</td>
 *  <td>Pixel intensity variation</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"DynamicRange"</td>
 *  <td>"config".<br/>"measures".<br/>"DynamicRange"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x49</td>
 *  <td>Sharpness</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"Sharpness"</td>
 *  <td>"config".<br/>"measures".<br/>"Sharpness"</td>
 *  <td><code>model_path</code>: Path to the random forest model file</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x4A</td>
 *  <td>Abscence of compression artifacts</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"NoCompressionArtifacts"</td>
 *  <td>"config".<br/>"measures".<br/>"NoCompressionArtifacts"</td>
 *  <td><code>model_path</code>: Path to OFIQ's compression artifact CNN in ONNX format</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x4B</td>
 *  <td>Colour naturality</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"NaturalColour"</td>
 *  <td>"config".<br/>"measures".<br/>"NaturalColour"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x4C</td>
 *  <td>Face uniqueness</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"SingleFacePresent"</td>
 *  <td>"config".<br/>"measures".<br/>"SingleFacePresent"</td>
 *  <td>none</td>
 *  <td>no</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x4D</td>
 *  <td>Eyes openess</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"EyesOpen"</td>
 *  <td>"config".<br/>"measures".<br/>"EyesOpen"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x4E</td>
 *  <td>Mouth closedness</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"MouthClosed"</td>
 *  <td>"config".<br/>"measures".<br/>"MouthClosed"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x4F</td>
 *  <td>Eyes visibility</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"EyesVisible"</td>
 *  <td>"config".<br/>"measures".<br/>"EyesVisible"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x50</td>
 *  <td>Mouth occlusion prevention</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"MouthOcclusionPrevention"</td>
 *  <td>"config".<br/>"measures".<br/>"MouthOcclusionPrevention"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x51</td>
 *  <td>Face occlusion prevention</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"FaceOcclusionPrevention"</td>
 *  <td>"config".<br/>"measures".<br/>"FaceOcclusionPrevention"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x52</td>
 *  <td>Inter-eye distance length</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"InterEyeDistance"</td>
 *  <td>"config".<br/>"measures".<br/>"InterEyeDistance"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x53</td>
 *  <td>Size of the head in the image</td>
 *  <td>"config".<br/>"params".<br/>"measures".<br/>"HeadSize"</td>
 *  <td>"config".<br/>"measures".<br/>"HeadSize"</td>
 *  <td>none</td>
 *  <td>yes - the argument to the quality mapping is \f$\|x-0.45\|\f$ where \f$x\f$ is the native quality score</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x54</td>
 *  <td>Leftward crop of the face image</td>
 *  <td>"config">"params".<br/>"measures".<br/>"LeftwardCropOfTheFaceImage"</td>
 *  <td>"config".<br/>"measures".<br/>"CropOfTheFaceImage"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x55</td>
 *  <td>Rightward crop of the face image</td>
 *  <td>"config">"params".<br/>"measures".<br/>"RightwardCropOfTheFaceImage"</td>
 *  <td>"config".<br/>"measures".<br/>"CropOfTheFaceImage"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x56</td>
 *  <td>Margin above of the face image</td>
 *  <td>"config">"params".<br/>"measures".<br/>"MarginAboveOfTheFaceImage"</td>
 *  <td>"config".<br/>"measures".<br/>"CropOfTheFaceImage"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x57</td>
 *  <td>Margin below of the face image</td>
 *  <td>"config">"params".<br/>"measures".<br/>"MarginBelowOfTheFaceImage"</td>
 *  <td>"config".<br/>"measures".<br/>"CropOfTheFaceImage"</td>
 *  <td>none</td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x58</td>
 *  <td>Pose angle yaw frontal alignment</td>
 *  <td>"config">-</td>
 *  <td>"config".<br/>"measures".<br/>"HeadPose"</td>
 *  <td>none</td>
 *  <td>no</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x59</td>
 *  <td>Pose angle pitch frontal alignment</td>
 *  <td>-</td>
 *  <td>"config".<br/>"measures".<br/>"HeadPose"</td>
 *  <td>none</td>
 *  <td>no</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x5A</td>
 *  <td>Pose angle roll frontal alignment</td>
 *  <td>-</td>
 *  <td>"config".<br/>"measures".<br/>"HeadPose"</td>
 *  <td>none</td>
 *  <td>no</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x5B</td>
 *  <td>Expression neutrality</td>
 *  <td>"config">"params".<br/>"measures".<br/>"ExpressionNeutrality"</td>
 *  <td>"config".<br/>"measures".<br/>"ExpressionNeutrality"</td>
 *  <td>
 *   <code>cnn_model_path1</code>: Path to the CNN model <i>enet_b0_8_best_vgaf_embed_zeroed.onnx</i> derived from 
 *   <a href="https://github.com/HSE-asavchenko/face-emotion-recognition">here</a> 
 *   in ONNX format
 *   <br/><br/>
 *   <code>cnn_model_path2</code>: Path to the CNN model <code>enet_b2_8_embed_zeroed.onnx</code> derived from 
 *   <a href="https://github.com/HSE-asavchenko/face-emotion-recognition">here</a> 
*    in ONNX format.
 *   <br/><br/>
 *   <code>adaboost_model_path</code>: Path to the AdaBoost classifier model file <code>hse_1_2_C_adaboost.yml.gz</code> from
 *   <a href="https://github.com/dasec/Efficient-Expression-Neutrality-Estimation">here</a>
 *  </td>
 *  <td>yes</td>
 *  </tr>
 *
 *  <tr>
 *  <td>0x5C</td>
 *  <td>Abscence of head coverings</td>
 *  <td>"config">"params".<br/>"measures".<br/>"NoHeadCovering"</td>
 *  <td>"config".<br/>"measures".<br/>"NoHeadCovering"</td>
 *  <td>
 *   <code>T0</code> - Proportion of pixels classified as head covering <= T0 will lead to a quality component value of 100 (best)<br/>
 *   <code>T1</code> - Proportion of pixels classified as head covering >= T1 will lead to a quality component value of 0 (worst)<br/>
 *   <code>w</code> -Proportion of pixels classified as head covering in (T0,T1) will be interpolated using a sigmoid function with w as standard deviation<br/>
 *   <code>x0</code> - Proportion of pixels classified as head covering in (T0,T1) will be interpolated using a sigmoid function with x0 as development point
 *  </td>
 *  <td>no</td>
 *  </tr>
 * </table>
 * 
 * @subsection sec_quality_config Configuration of the quality mapping
 * Each measure implemented in OFIQ outputs a pair of values. The first
 * value is called <i>native quality score</i>. The second value is called
 * <i>quality component value</i> which is an integer between 0 (worst quality)
 * and 100 (best quality). The quality component value and is derived from 
 * the <i>native quality score</i> using a mapping function. Whether this mapping
 * function can be configured for the measure is stated in the table of 
 * section @ref sec_default_config.
 * <br/>
 * <br/>
 * Note, the OFIQ library implements hard-coded default quality 
 * mappings as a fallback.
 * <br/>
 * <br/>
 * A configurable quality mapping has the form of
 * \f[
 * Q(h,a,s,x,x_0,w)=h\cdot(a+s\cdot\mathrm{sigmoid}(x,x_0,w))
 * \f]
 * where
 * \f[
 * \mathrm{sigmoid}(x,x_0,w)=(1+\exp((x_0-x)/w)^{-1}.
 * \f]
 * Note, \f$x\f$ is the native quality score which is mapped to the quality component value.
 * The other symbols denote parameters that can be configured (see the example at the end of this section).
 * <table>
 *  <tr>
 *   <td><b>parameter</b></td>
 *   <td><b>description</b></td>
 *   <td><b>default value</b></td>
 *  </tr>
 *  <tr>
 *   <td>"h"</td>
 *   <td>scale factor</td>
 *   <td>100</td>
 *  </tr>
 *  <tr>
 *   <td>"a"</td>
 *   <td>constant shift</td>
 *   <td>0</td>
 *  </tr>
 *  <tr>
 *   <td>"s"</td>
 *   <td>signed weight for sigmoid part</td>
 *   <td>1</td>
 *  </tr>
 *  <tr>
 *   <td>"x0"</td>
 *   <td></td>center point within sigmoid function;
 *   the default value has been chosen arbitrarily and should specified when a mapping is configured.</td>
 *   <td>4</td>
 *  </tr>
 *  <tr>
 *   <td>"w"
 *   </td>
 *   <td>divisor within the sigmoid function; 
 *   the default value has been chosen arbitrarily and should specified when a mapping is configured.</td>
 *   <td>0.7</td>
 *  </tr>
 *  <tr>
 *   <td>"round"</td>
 *   <td>applies the compiler's native rounding function (<code>std::round</code>) such that only integer 
 *   values are used as the quality value</td><td>true</td>
 *  </tr>
 * </table>
 * All parameters are optional and can be omitted. In this case, the default value is chosen.
 * Note, if a mapping results in a value not within 0 and 100,
 * then a clipping is applied choosing the value 0 or 100 being closest to the mapped
 * value.
 * <br/>
 * <br/>
 * For example, OFIQ's configuration for the background uniformity measure looks as follows
 * <pre>
 * {
 *   "config" :
 *   ...
 *   "params": {
 *      ...
 *      "BackgroundUniformity": {
 *        "Sigmoid" : {
 *          "h": 190,
 *          "a": 1,
 *          "s": -1,
 *          "x0": 10,
 *          "w" : 100,
 *          "round": true
 *        }
 *      }
 *      ...
 *   }
 * }
 * </pre>
 * 
 * @section sec_api C++ API
 * To use OFIQ in a C++ application one needs to include the following header file.
 * <pre>
 * #include <ofiq_lib.h>
 * </pre>
 * In the following, we assume that the namespace \link OFIQ OFIQ\endlink and \link OFIQ_LIB OFIQ_LIB\endlink are used.
 * <pre>
 * using namespace OFIQ;
 * using namespace OFIQ_LIB;
 * </pre>
 * An OFIQ instance is initialized using 
 * the \link OFIQ::Interface Interface\endlink class as follows.
 * <pre>
 *   // Get implementation pointer
 *   auto implPtr = Interface::getImplementation();
 *   // Initialization
 *   auto ret = implPtr->initialize(configDir,configFile);
 * </pre>
 * Here <code>configDir</code> is a <code>std::string</code>-representation of the path to the 
 * directory in which a JAXN configuration file of name <code>configFile</code> 
 * is stored - as documented in the @ref sec_config "configuration section". Note, that the path
 * can be absolute or relative to the path of the current working directory.
 * <br />
 * <br />
 * The input image is read by using
 * the \link OFIQ_LIB::readImage readImage\endlink function as follows
 * <pre>
 *   Image image;
 *   ReturnStatus retStatus = readImage(imagePath, image);
 * </pre>
 * where <code>imagePath</code> is a <code>std::string</code>-representation of a path to
 * an image file. The representation is written to the <code>image</code> object of
 * type \link OFIQ::Image Image\endlink.
 * <br/>
 * <br/>
 * To compute the quality assessments, run
 * <pre>
 * FaceImageQualityAssessment assessment;
 * ReturnStatus retStatus = implPtr->vectorQuality(image, assessment);
 * </pre>
 * A successful computation is indicated by <code>retStatus.code</code> if it is of value 
 * \link OFIQ::ReturnCode::Success ReturnCode::Success\endlink. Then the assessment result is stored in a 
 * \link OFIQ::FaceImageQualityAssessment FaceImageQualityAssessment\endlink struct object. The obtained
 * \link OFIQ::FaceImageQualityAssessment FaceImageQualityAssessment\endlink object
 * has a <code>std::map</code> member which, for a specified \link OFIQ::QualityMeasure QualityMeasure\endlink
 * key, returns the \link OFIQ::QualityMeasureResult QualityMeasureResult\endlink. A
 * \link OFIQ::QualityMeasureResult QualityMeasureResult\endlink struct object contains the native quality
 * score stored in the \link OFIQ::QualityMeasureResult::rawScore rawScore\endlink member and the
 * quality component value stored in the \link OFIQ::QualityMeasureResult::scalar scalar\endlink
 * member. Note, both members are encoded as a <code>double</code> values although the 
 * \link OFIQ::QualityMeasureResult::scalar scalar\endlink member should 
 * (on successful quality measure computation) be an integer value between 0 and 100. To check whether
 * a \link OFIQ::QualityMeasureResult QualityMeasureResult\endlink has been computed successfully, one
 * checks if its \link OFIQ::QualityMeasureResult::code code\endlink member agrees with the value
 * \link OFIQ::QualityMeasureReturnCode::Success QualityMeasureReturnCode::Success\endlink.
 * 
 * @section sec_workflow Implementation and pre-processing workflow
 * Quality assessment is controlled by the implementation of 
 * the \link OFIQ_LIB::OFIQImpl OFIQImpl\endlink class. A shared pointer to an
 * \link OFIQ_LIB::OFIQImpl OFIQImpl\endlink object is returned by the 
 * \link OFIQ::Interface::getImplementation() Interface::getImplementation()\endlink
 * function. The implementation needs to be initialized once using the
 * \link OFIQ_LIB::OFIQImpl::initialize() OFIQImpl::initialize()\endlink function. Note, the 
 * \link OFIQ_LIB::OFIQImpl::initialize() OFIQImpl::initialize()\endlink function 
 * loads all model files as specified in the input configuration into memory; thus,
 * one should avoid creating repeated instances of the \link OFIQ_LIB::OFIQImpl OFIQImpl\endlink.
 * 
 * After successful initialization, the implementation object can be used and one can
 * repeatedly invoke the 
 * \link OFIQ_LIB::OFIQImpl::vectorQuality() OFIQImpl::vectorQuality()\endlink function
 * to assess the quality of a series of facial images.
 * 
 * The internal workflow of the \link OFIQ_LIB::OFIQImpl::vectorQuality() OFIQImpl::vectorQuality()\endlink
 * implementation is as follows.
 * <ol>
 *  <li>
 *   Pre-processing of the input image using the \link OFIQ_LIB::OFIQImpl::performPreprocessing() OFIQImpl::performPreprocessing()\endlink function.
 *   <ol>
 *    <li>Face detection implemented by \link OFIQ_LIB::modules::detectors::SSDFaceDetector::UpdateFaces() SSDFaceDetector::UpdateFaces()\endlink</li>.
 *    <li>Pose estimation implemented by \link OFIQ_LIB::modules::poseEstimators::HeadPose3DDFAV2::updatePose() HeadPose3DDFAV2::updatePose()\endlink</li>.
 *    <li>Landmark extraction implemented by \link OFIQ_LIB::modules::landmarks::ADNetFaceLandmarkExtractor::updateLandmarks() ADNetFaceLandmarkExtractor::updateLandmarks()\endlink</li>.
 *    <li>Facial alignment implemented by \link OFIQ_LIB::OFIQImpl::alignFaceImage() OFIQImpl::alignFaceImage()\endlink.
 *    <li>Face parsing implemented by \link OFIQ_LIB::modules::segmentations::FaceParsing::UpdateMask() FaceParsing::UpdateMask()\endlink.
 *    <li>Face occlusion segmentation implemented by \link OFIQ_LIB::modules::segmentations::FaceOcclusionSegmentation::UpdateMask() FaceOcclusionSegmentation::UpdateMask()\endlink.
 *   </ol>
 *  </li>
 *  <li>
 *   Quality assessment using the \link OFIQ_LIB::modules::measures::Executor::ExecuteAll() Executor::ExecuteAll()\endlink function:
 *   For all requested measures
 *   <ol>
 *    <li>its \link OFIQ_LIB::modules::measures::Measure::Execute() Execute()\endlink
 *    <li>and then its  \link OFIQ_LIB::modules::measures::Measure::SetQualityMeasure() SetQualityMeasure()\endlink functions are invoked.
 *   </ol>
 *  </li>
 * </ol>
 * 
 * @section sec_tutorial_new_measure Tutorial: Extending OFIQ
 * This section describes how to extend OFIQ by a new measure. We will choose 
 * an easy measure to illustrate the process. Therefore, we extend OFIQ by 
 * a somewhat dummy measure that assesses the subject's 
 * <i>non-surprisedness</i>. We will measure the 
 * surprisedness by the flatness of the eye-brow using the eye-brow landmarks.
 * <br/><br/>
 * Create a header file <code>NonSurprisedness.h</code> in the directory 
 * <code>/path/to/OFIQ-Project/OFIQlib/modules/</code>
 * <code>measures/</code> with the following content
 * <pre>
 * \#pragma once
 * 
 * \#include "landmarks.h"
 * \#include "Measure.h"
 *
 * namespace OFIQ_LIB::modules::measures
 * {
 *     class NonSurprisedness : public Measure
 *     {
 *         public:
 *           explicit NonSurprisedness(const Configuration& configuration);
 *
 *           void Execute(OFIQ_LIB::Session & session) override;
 *   };
 * }
 * </pre>
 * Also, create a source file <code>NonSurprisedness.cpp</code> in the directory
 * <code>/path/to/OFIQ-Project/OFIQlib/modules/measures/src/</code> with the following content.
 * <pre>
 * \#include "NonSurprisedness.h"
 * \#include "FaceMeasures.h"
 * \#include "FaceParts.h"
 *
 * using FaceMeasures = OFIQ_LIB::modules::landmarks::FaceMeasures;
 *
 * namespace OFIQ_LIB::modules::measures
 * {
 *     static const auto qualityMeasure = OFIQ::QualityMeasure::NonSurprisedness;
 *
 *     NonSurprisedness::NonSurprisedness(const Configuration& configuration)
 *         : Measure{ configuration, qualityMeasure }
 *     {
 *         // Implement me
 *     }
 *
 *     void NonSurprisedness::Execute(OFIQ_LIB::Session & session)
 *     {
 *         // Implement me
 *     }
 * }
 * </pre>
 * To make the source code to compile, we need to extend the enumeration <code>OFIQ::QualiyMeasure</code>
 * by the new measure. Therefore, edit the file <code>/path/to/OFIQ-Project/OFIQlib/include/ofiq_structs.h</code>
 * and insert the item
 * <pre>
 *   NonSurprisedness
 * </pre>
 * within the enumeration <code>OFIQ::QualiyMeasure</code>. The resulting <code>ofiq_struct.h</code> could 
 * look like this.
 * <pre>
 * ...
 * namespace OFIQ
 * {
 *     ...
 *     enum class QualityMeasure
 *     {
 *         // UnifiedQualityScore
 *         UnifiedQualityScore = 0x41,
 *         ...
 *         // Newly inserted NonSurprisedness measure
 *         NonSurprisedness,
 *         // unknown measure
 *         NotSet = -1
 *     }
 *     ...
 * }
 * </pre>
 * Then add the new header to <code>/path/to/OFIQ-Project/OFIQlib/modules/measures/AllMeasures.h</code>
 * <pre>
 * ...
 * \#include "UnifiedQualityScore.h"
 * \#include "NonSurprisedness.h"
 * </pre>
 * and include the new measure in the file <code>/path/to/OFIQ-Project/OFIQlib/modules/measures/src/MeasureFactory.cpp</code>
 * <pre>
 * static const std::map<OFIQ\::QualityMeasure, 
 *     std::function<std::unique_ptr<Measure>(const Configuration&)>> factoryMapping
 * {
 *     {OFIQ::QualityMeasure::SingleFacePresent, [](const Configuration& configuration) 
 *         { return std::make_unique<SingleFacePresent>(configuration); }},
 *     ...
 *     {OFIQ::QualityMeasure::NonSurprisedness, [](const Configuration& configuration) 
 *         { return std::make_unique<NonSurprisedness>(configuration); }},
 * }
 * </pre>
 * If we are on Windows, we need to edit insert the new header 
 * file <code>NonSurprisedness.h</code> and the new 
 * source file <code>NonSurprisedness.cpp</code> in the 
 * file <code>/path/to/OFIQ-Project/OFIQLib/CMakeLists.windows.cmake</code>.
 * The resulting <code>CMakeLists.windows.cmake</code> could look like this.
 * <pre>
 *  list(APPEND module_sources 
 *    ${libImplementationSources}
 *    ...
 *    ${OFIQLIB_SOURCE_DIR}/modules/measures/src/NonSurprisedness.cpp
 *    ...
 *
 *  list(APPEND module_headers
 *    ${PUBLIC_HEADER_LIST}
 *    ...
 *    ${OFIQLIB_SOURCE_DIR}/modules/measures/NonSurprisedness.h
 *    ...
 * </pre>
 * Likewise, if we are on Ubuntu or MacOS, we need to edit the files
 * <code>CMakeLists.ubuntu.cmake</code> or <code>CMakeLists.macos.cmake</code>, respectively.
 * Note, for Ubuntu or MacOS we only need to insert the 
 * file <code>NonSurprisedness.cpp</code> 
 * (and not the file <code>NonSurprisedness.h</code>). 
 * <br/><br/>
 * After having finished the above steps, we may already build OFIQ 
 * by performing the steps described in  the building steps. However, after
 * compiling and running OFIQ, we may note that no output for our new
 * no-surprisedness measure is made. Therefore, two additional steps 
 * need to be done:
 * <ol>
 *  <li>Edit OFIQ's configuration file</li>
 *  <li>Implement the member functions of the 
 *   class <code>NonSurprisedness</code></li>
 * </ol>
 * To edit OFIQ's default configuration file, open <code>/path/to/OFIQ-Project/data/ofiq_config.jaxn</code>
 * and include the NonSurprisedness measure. The 
 * resulting <code>ofiq_config.jaxn</code> could look like this.
 * <pre>
 *  ...
 *  "config": {
 *   ...
 *   "measures": [
 *     ...
 *     "NonSurprisedness",
 *     ...
 *   ],
 *   ...
 * </pre>
 * To implement the <code>Execute</code> method, we may want to compute
 * the native quality measure first. 
 * At this point, we should define the non-surprisedness measure. For an eye-brow,
 * we define the non-surprisedness using the difference of the y-coordinates
 * of the northern eye-brow landmark to the y-coordinate between the left and the 
 * right eye-brow coordinate. To make the non-surprisedness independent from
 * the facial image's resolution we divide the difference by the width of the eye-brow.
 * the right eye-brow landmarks divided by the distance between the left and right
 * The non-surprisedness is computed for the left and right eye-brow
 * and then the minimum of the two eye brow's non-surprisedness as the overall
 * non-surprisedness. The following functions computes the non-surprisedness for
 * an eye-brow.
 * <pre>
 * static double GetNonSurprisedness(
 *     const OFIQ\::LandmarkPoint & north,
 *     const OFIQ\::LandmarkPoint & left,
 *     const OFIQ\::LandmarkPoint & right)
 * {
 *     auto middle = FaceMeasures::GetMiddle(OFIQ::Landmarks{ left,right });
 *     double diff = std::abs(middle.y-north.y);
 *     double width = FaceMeasures::GetDistance(left,right);
 *     return diff / width; // Results in NaN, when dividing by zero
 * }
 * </pre>
 * The function <code>NonSurprisedness</code> uses functions provided 
 * by <code>FaceMeasures.h</code>.
 * Now, we can implement the <code>Execute</code> method.
 * <pre>
 * void NonSurprisedness::Execute(OFIQ_LIB::Session & session)
 * {
 *     auto landmarks = session.getAlignedFaceLandmarks();
 *     double leftNonSurprisedness = GetNonSurprisedness(landmarks.landmarks[33],
 *         landmarks.landmarks[38],landmarks.landmarks[35]);
 *     double rightNonSurprisedness = GetNonSurprisedness(landmarks.landmarks[50],
 *         landmarks.landmarks[46],landmarks.landmarks[44]);
 *     double nonSurprisedness = 
 *         std::min(leftNonSurprisedness, rightNonSurprisedness);
 *     if (std::isnan(nonSurprisedness))
 *     {
 *         // If the measure is NaN, we cannot compute
 *         // the non-surprisedness and should indicate
 *         // this by ’FailureToAssess’
 *         SetQualityMeasure(session, qualityMeasure, nonSurprisedness, 
 *             OFIQ\::QualityMeasureReturnCode::FailureToAssess);
 *     }
 *     else
 *     {
 *         SetQualityMeasure(session, qualityMeasure, nonSurprisedness,
 *             OFIQ\::QualityMeasureReturnCode::Success);
 *     }
 * }
 * </pre> 
 * The measure will automatically map the non-surprisedness measure to 
 * a quality values that is an integer between 0 and 100. For that, a
 * default mapping is applied (see Section @ref sec_quality_config).
 * We should change the default mapping in the constructor. Therefore,
 * we choose a mapping with the help of a sigmoid function that maps
 * high non-surprisedness values to high quality values and vice-versa.
 * <pre>
 * NonSurprisedness::NonSurprisedness(const Configuration& configuration)
 *     : Measure{ configuration, qualityMeasure }
 * {
 *     SigmoidParameters defaultValues;
 *     defaultValues.h = 100;
 *     defaultValues.x0 = 0.5;
 *     defaultValues.w = 1.0;
 *     defaultValues.round = true;
 *     AddSigmoid(qualityMeasure, defaultValues);
 * }
 * </pre>
 * The above mapping is a fallback for the case when the mapping is not configured in the configuration file.
 * To configure the mapping in the configuration file, edit the <code>ofiq_config.jaxn</code> so that
 * it is of the form
 * <pre>
 *    "config": {
 *      ...
 *      "params" : {
 *         ...
 *         "measures": {
 *            ...
 *            "NonSurprisedness" : {
 *              "Sigmoid" : { 
 *                "h": 100,
 *                "x0": 0.5,
 *                "w": 1.0,
 *                "round": true
 *              }
 *            }, ...
 * </pre>
 *
 * @section sec_release_notes Release notes
 * This is OFIQ v1.0.2. 
 * The following table lists all measures and its implementation provided by this release of OFIQ. Details on the 
 * configuration and on requesting measures can be found
 * @ref sec_default_config "here". Note, the QAA identifiers listed in the table are defined in ISO/IEC 29794-5.
 * <table>
 *  <tr>
 *   <td><b>QAA identifier</b></td>
 *   <td><b>Description</b></td>
 *   <td><b>OFIQ implementation reference</b></td>
 *  </tr>
 *
 *  <tr>
 *   <td>0x41</td>
 *   <td>[MagFace](https://github.com/IrvingMeng/MagFace)-based unified quality score measure.</td>
 *   <td>\link OFIQ_LIB::modules::measures::UnifiedQualityScore UnifiedQualityScore\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x42</td>
 *   <td>Gradient-based background uniformity.</td>
 *   <td>\link OFIQ_LIB::modules::measures::BackgroundUniformity BackgroundUniformity\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x43</td>
 *   <td>Illumination uniformity by summing up the minima of the histograms of the left and the right side of the face.</td>
 *   <td>\link OFIQ_LIB::modules::measures::IlluminationUniformity IlluminationUniformity\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x44</td>
 *   <td>Luminance mean measure computed from the luminance histogram</td>
 *   <td>\link OFIQ_LIB::modules::measures::Luminance Luminance\endlink</td>
 *  </tr>
 *
 *  <tr>
 *   <td>0x45</td>
 *   <td>Luminance variance measure computed from the luminance histogram</td>
 *   <td>\link OFIQ_LIB::modules::measures::Luminance Luminance\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x46</td>
 *   <td>Under-exposure prevention by computing the proportion
 *   of low-intensity pixels in the luminance image to assess the abscence of under-exposure</td>
 *   <td>\link OFIQ_LIB::modules::measures::UnderExposurePrevention UnderExposurePrevention\endlink</td>
 *  </tr>
 *
 *  <tr>
 *   <td>0x47</td>
 *   <td>Over-exposure prevention by computing the proportion
 *   of high-intensity pixels in the luminance image to assess the abscence of over-exposur</td>
 *   <td>\link OFIQ_LIB::modules::measures::OverExposurePrevention OverExposurePrevention\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x48</td>
 *   <td>Dynamic range computed from the luminance histogram.</td>
 *   <td>\link OFIQ_LIB::modules::measures::DynamicRange DynamicRange\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x49</td>
 *   <td>Sharpness assessment based on a random forest classifier trained by the 
 *   OFIQ development team.</td>
 *   <td>\link OFIQ_LIB::modules::measures::Sharpness Sharpness\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x4A</td>
 *   <td>Assessment of the absence of compression artifact (both JPEG and JPEG2000) based on a 
 *   CNN trained by the OFIQ development team.</td>
 *   <td>\link OFIQ_LIB::modules::measures::CompressionArtifacts CompressionArtifacts\endlink</td>
 *  </tr>
 * 
  *  <tr>
 *   <td>0x4B</td>
 *   <td>Assessment of the naturalness of the colour based on the conversion of the 
 *   RGB presentation of the image to the CIELAB colour space.</td>
 *   <td>\link OFIQ_LIB::modules::measures::NaturalColour NaturalColour\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x4C</td>
 *   <td>Assessment of the uniqueness of the most dominant face detected by comparing its size 
 *   with the size of the second largest face detected</td>
 *   <td>\link OFIQ_LIB::modules::measures::SingleFacePresent SingleFacePresent\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x4D</td>
 *   <td>Eyes openness assessment based on computing eyes aspect ratio from eye landmarks</td>
 *   <td>\link OFIQ_LIB::modules::measures::EyesOpen EyesOpen\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x4E</td>
 *   <td>Mouth closed assessment based on computing a ratio from mouth landmarks</td>
 *   <td>\link OFIQ_LIB::modules::measures::MouthClosed MouthClosed\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x4F</td>
 *   <td>Eyes visibility assessment by measuring the coverage of the eye visibility zone with
 *   the result of face occlusion segmentation computed during pre-processing.</td>
 *   <td>\link OFIQ_LIB::modules::measures::EyesVisible EyesVisible\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x50</td>
 *   <td>Assessment of the absence of mouth occlusion by measuring the coverage of the mouth region
 *   from mouth landmarks with the result of face occlusion segmentation computed on pre-processing.</td>
 *   <td>\link OFIQ_LIB::modules::measures::MouthOcclusionPrevention MouthOcclusionPrevention\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x51</td>
 *   <td>Assessment of the absence of face occlusion by measuring the coverage of the landmarked region
 *   with the result of face occlusion segmentation computed during pre-processing.</td>
 *   <td>\link OFIQ_LIB::modules::measures::FaceOcclusionPrevention FaceOcclusionPrevention\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x52</td>
 *   <td>Inter-eye distance assessment based on computing the Euclidean length of eyes' centres
 *   and multiplication with the secant of the yaw angle computed during pre-processing.</td>
 *   <td>\link OFIQ_LIB::modules::measures::InterEyeDistance InterEyeDistance\endlink</td>
 *  </tr>
 *
 *  <tr>
 *   <td>0x53</td>
 *   <td>Size of the head based on computing the height of the face computed from facial landmarks
 *   with the height of the image.</td>
 *   <td>\link OFIQ_LIB::modules::measures::HeadSize HeadSize\endlink</td>
 *  </tr>
 *
 *  <tr>
 *   <td>0x54</td>
 *   <td>Leftward crop of the face image</td>
 *   <td>\link OFIQ_LIB::modules::measures::CropOfTheFaceImage CropOfTheFaceImage\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x55</td>
 *   <td>Rightward crop of the face image</td>
 *   <td>\link OFIQ_LIB::modules::measures::CropOfTheFaceImage CropOfTheFaceImage\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x56</td>
 *   <td>Margin above of the face image</td>
 *   <td>\link OFIQ_LIB::modules::measures::CropOfTheFaceImage CropOfTheFaceImage\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x57</td>
 *   <td>Margin below of the face image</td>
 *   <td>\link OFIQ_LIB::modules::measures::CropOfTheFaceImage CropOfTheFaceImage\endlink</td>
 *  </tr>
 *  
 *  <tr>
 *   <td>0x58</td>
 *   <td>Pose angle yaw frontal alignment based on the [3DDFAV2](https://github.com/cleardusk/3DDFA_V2).</td>
 *   <td>\link OFIQ_LIB::modules::measures::HeadPose HeadPose\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x59</td>
 *   <td>Pose angle pitch frontal alignment based on the [3DDFAV2](https://github.com/cleardusk/3DDFA_V2)</td>
 *   <td>\link OFIQ_LIB::modules::measures::HeadPose HeadPose\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x5A</td>
 *   <td>Pose angle roll frontal alignment based on the [3DDFAV2](https://github.com/cleardusk/3DDFA_V2)</td>
 *   <td>\link OFIQ_LIB::modules::measures::HeadPose HeadPose\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x5B</td>
 *   <td>Expression neutrality estimation based on a fusion of [HSEMotion](https://github.com/HSE-asavchenko/face-emotion-recognition) with 
 *   with [Efficient-Expression-Neutrality-Estimation](https://github.com/dasec/Efficient-Expression-Neutrality-Estimation).</td>
 *   <td>\link OFIQ_LIB::modules::measures::ExpressionNeutrality ExpressionNeutrality\endlink</td>
 *  </tr>
 * 
 *  <tr>
 *   <td>0x5C</td>
 *   <td>Assessment of the absence of head coverings by counting the pixels being labeled 
 *   as head covers in the mask output by the face parsing computed during pre-processing.</td>
 *   <td>\link OFIQ_LIB::modules::measures::NoHeadCoverings NoHeadCoverings\endlink</td>
 *  </tr>
 * 
 * </table>
 *
 * @subsection sec_changelog Changelog
 * @includedoc "../../CHANGELOG.md"
 */
#pragma once